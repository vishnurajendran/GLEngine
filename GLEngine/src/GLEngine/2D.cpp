#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLEngine/2D.h"
#include "GLEngine/Debugging.h"
#include "GLEngine/ResourceManager.h"
#include "GLEngine/Core/ViewManagement.h"
namespace GLengine {
#define PI 3.1415926535898

	void Sprite2D::GenerateShapeAttribs() {
		vertices = new float[] {
			// positions			// colors           // texture coords
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
				0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
				-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left 
		};

		vertSize = 32;

		indices = new unsigned int[] {
			0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

		indxSize = 6;
	}

	void Sprite2D::SetTransformationMatrix() {

		glm::mat4 view = ViewManager::GetViewMatrix();
		glm::mat4 projection = ViewManager::GetProjectionMatrix();
		view = glm::translate(view, GetTransform()->position);
		shape->SetModelMatrix(GetTransform()->GetModelTransformationMatrix());
		shape->SetViewMatrix(view);
		shape->SetProjectionMatrix(projection);
	}

	void Sprite2D::DrawSprite() {
		GetTransform()->UpdateVectors();
		shape->PrepareToDraw();
		SetTransformationMatrix();
		shape->Draw();
	}

	Sprite2D::Sprite2D() {
		GenerateShapeAttribs();
		ResourceManager::CreateShader("def_sprite_shader", "Assets/Shaders/Sprite2D/Sprite2DShader.shader");
		ResourceManager::CreateTexture2D("def_sprite_tex", "Assets/Images/Defaults/Sprite.jpg", 0, TextureFormat::RGB, TextureWrap::Repeat, 0);

		Shader* spriteShader = ResourceManager::GetShader("def_sprite_shader");
		Texture2D* spriteTexture = new Texture2D{
			*ResourceManager::GetTexture2D("def_sprite_tex")
		};

		ResourceManager::CreateMaterial("def_sprite_material", spriteShader, spriteTexture, 1);
		Material* spriteMaterial = ResourceManager::GetMaterial("def_sprite_material");

		shape = new Shape2D(vertices, vertSize, indices, indxSize, spriteMaterial);
	}

	Sprite2D::Sprite2D(Material* material) {
		GenerateShapeAttribs();
		shape = new Shape2D(vertices, vertSize, indices, indxSize, material);
	}

	Sprite2D::Sprite2D(Texture2D* texture) {
		GenerateShapeAttribs();
		ResourceManager::CreateShader("def_sprite_shader", "Assets/Shaders/Sprite2D/Sprite2DShader.shader");
		Shader* spriteShader = ResourceManager::GetShader("def_sprite_shader");

		Texture2D* spriteTexture = new Texture2D{
			*texture
		};

		std::string matKey = ResourceManager::CreateMaterial(spriteShader, spriteTexture, 1);
		Material* spriteMaterial = ResourceManager::GetMaterial(matKey);
		shape = new Shape2D(vertices, vertSize, indices, indxSize, spriteMaterial);
	}

	void Sprite2D::Start()
	{
		//nothing here for now
	}

	void Sprite2D::Update()
	{
		DrawSprite();
	}

	void Sprite2D::OnDestroy()
	{
		this->~Sprite2D();
	}
}

