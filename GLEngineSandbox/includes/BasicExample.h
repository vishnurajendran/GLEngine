#pragma once
#include <string>
#include <GLEngine.h>

class BasicExampleComponent :public GLengine::IComponent {
	GLengine::Camera* activeCamera;
	GLengine::Sprite2D* bird;
	GLengine::TextComponent* textComp;
public:

	void Start();
	void Update();
	void OnDestroy();
	void OnCollide(GLengine::Collision2D* collision);
};

class BasicExampleGame :public GLengine::Game {
	GLengine::Camera* mainCamera;
	GLengine::Sprite2D* bg;
	GLengine::Sprite2D* birdSprite;
	GLengine::GameObject* bgGO;
	GLengine::GameObject* bird;
	GLengine::GameObject* musicSource;
	BasicExampleComponent* example;
public:
	void Start();
	void Loop();
	void Exit();
};