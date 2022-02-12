#include <iostream>
#include "GLEngine/Core/GameObject.h"
#include "GLEngine/Core/Component.h"
#include "GLEngine/Debugging.h"

namespace GLengine {
#pragma region GameObject

	GameObject::GameObject() {
		gameObjectID = GameObjectManager::GetUniqueGameObjectID();
		name = "GameObject " + std::to_string(gameObjectID);
		GameObjectManager::AddToGameObjects(this);
	}

	GameObject::GameObject(std::string name) {
		gameObjectID = GameObjectManager::GetUniqueGameObjectID();
		this->name = name;
		GameObjectManager::AddToGameObjects(this);
	}

	void GameObject::AttachComponent(IComponent* component) {
		attachedComponents.push_back(component);
		component->OnAttached(this);
		component->Start();
	}

	void GameObject::UpdateGameObject() {
		for (IComponent* compoenent : attachedComponents) {
			compoenent->Update();
		}
	}

	void GameObject::Destroy() {
		for (IComponent* compoenent : attachedComponents) {
			compoenent->OnDestroy();
		}

		this->~GameObject();
	}

	int GameObject::GetID() {
		return gameObjectID;
	}

	bool operator == (GameObject& lhs, GameObject& rhs) {
		return lhs.GetID() == rhs.GetID();
	}

	GameObject::~GameObject() {
		GameObjectManager::RemoveFromGameObjects(this);
	}

#pragma endregion

#pragma region Game Object Manager

	std::vector<GameObject*> GameObjectManager::gameObjects;
	int GameObjectManager::idCounter = 0;

	int GameObjectManager::GetUniqueGameObjectID() {
		return idCounter++;
	}

	void GameObjectManager::AddToGameObjects(GameObject* gameObject) {
		gameObjects.push_back(gameObject);
	}

	void GameObjectManager::RemoveFromGameObjects(GameObject* gameObject) {
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
	}

	void GameObjectManager::UpdateGameObjects() {
		for (GameObject* gameObject : gameObjects) {
			gameObject->UpdateGameObject();
		}
	}

	void GameObjectManager::Cleanup() {
		LogInfo("Cleaning up game objects");
		for (GameObject* gameObject : gameObjects) {
			gameObject->Destroy();
		}

		gameObjects.clear();
	}

#pragma endregion
}