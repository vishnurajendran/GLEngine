#pragma once
#include<vector> 
#include<string>

#include "Core.h"
#include "Transform.h"

namespace GLengine {
#ifndef GAMEOBJECT
#define GAMEOBJECT

	//GameObject
	class IComponent;
	class GLENGINE_API GameObject {
		int gameObjectID;
		std::vector<IComponent*> attachedComponents;
	public:
		std::string name;
		Transform transform;
		GameObject();
		GameObject(std::string name);
		~GameObject();
		int GetID();
		void AttachComponent(IComponent* component);
		void UpdateGameObject();
		void Destroy();

		template <typename T>
		T* GetAttachedComponent();
	};

	template<typename Base, typename T>
	inline bool instanceof(const T*) {
		return std::is_base_of<Base, T>::value;
	}

	template<typename T>
	T* GameObject::GetAttachedComponent() {
		for (IComponent* component : attachedComponents) {
			if (instanceof<T>((T*)component))
				return (T*)component;
		}

		return NULL;
	}

	class GLENGINE_API GameObjectManager {
		static int idCounter;
		static std::vector<GameObject*> gameObjects;
	public:
		static int GetUniqueGameObjectID();
		static void AddToGameObjects(GameObject* gameObject);
		static void RemoveFromGameObjects(GameObject* gameObject);
		static void UpdateGameObjects();
		static void Cleanup();
	};

#endif
}