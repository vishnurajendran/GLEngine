#include <string>
#include "BasicExample.h"

#pragma region Component
void BasicExampleComponent::Start() {
	GLengine::Log("Example Started");
	this->activeCamera = GLengine::ViewManager::GetActiveCamera();
	GLengine::GameObject* obj = GetGameObject();
	GLengine::Log(obj->name.c_str());
	if (obj != NULL) {
		bg = GetGameObject()->GetAttachedComponent<GLengine::Sprite2D>();
	}
	else {
		GLengine::Log("Sprite2D Component not attached");
	}
}

void BasicExampleComponent::Update() {
	glm::vec3 inputVector = glm::vec3(GLengine::Input::GetInputVector().x, GLengine::Input::GetInputVector().y * 1, 0);
	GetTransform()->position += (inputVector * GLengine::Time::deltaTime);
}

void BasicExampleComponent::OnDestroy() {
	GLengine::Log("Example Destroyed");
}
#pragma endregion

#pragma region BasicExampleGame

void BasicExampleGame::Start() {

	GLengine::Log("Flappy clone started");

	mainCamera = new GLengine::Camera(true);
	mainCamera->orthoSize = 0.75f;
	mainCamera->transform.position = glm::vec3(0, 0, 1);
	GLengine::ResourceManager::CreateTexture2D("BG_Tex", "Assets/Images/Flappy/BG.png", 0, GLengine::TextureFormat::RGB, GLengine::TextureWrap::Repeat, 0);
	GLengine::ResourceManager::CreateTexture2D("Bird_Tex", "Assets/Images/Flappy/Bird.png", 0, GLengine::TextureFormat::RGBA, GLengine::TextureWrap::Repeat, 0);
	
	//Adding BG
	bg = new GLengine::Sprite2D(GLengine::ResourceManager::GetTexture2D("BG_Tex"));
	bgGO = new GLengine::GameObject("BG");
	bgGO->transform.localScale = glm::vec3(2, 1, 1);
	bgGO->transform.position = glm::vec3(0, 0, 0);
	bgGO->AttachComponent(bg);

	//Adding Bird
	example = new BasicExampleComponent();
	bird = new GLengine::GameObject("Bird");
	birdSprite = new GLengine::Sprite2D(GLengine::ResourceManager::GetTexture2D("Bird_Tex"));
	
	bird->transform.localScale *= 0.15f;
	bird->transform.position = glm::vec3(0.0f, 0.0f, 0.1f);
	bird->AttachComponent(birdSprite);
	bird->AttachComponent(example);
}

void BasicExampleGame::Loop() {
		
}

void BasicExampleGame::Exit() {
	GLengine::Log("Quiting Game");
}

#pragma endregion


GLengine::Game* GLengine::CreateGame() {
	return new BasicExampleGame();
}
std::string GLengine::GetGameName() {
	return "Basic Example";
}