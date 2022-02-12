#pragma once
#include <string>
#include <GLEngine.h>

class BasicExampleComponent :public GLengine::IComponent {
	GLengine::Camera* activeCamera;
	GLengine::Sprite2D* bg;
	GLengine::Sprite2D* bird;
public:

	void Start();
	void Update();
	void OnDestroy();
};

class BasicExampleGame :public GLengine::Game {
	GLengine::Camera* mainCamera;
	GLengine::Sprite2D* bg;
	GLengine::Sprite2D* birdSprite;
	GLengine::GameObject* bgGO;
	GLengine::GameObject* bird;
	BasicExampleComponent* example;
public:
	void Start();
	void Loop();
	void Exit();
};