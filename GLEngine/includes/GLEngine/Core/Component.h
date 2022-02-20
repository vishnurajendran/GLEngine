#pragma once
#include "Core.h"
#include "Transform.h"

namespace GLengine {
#ifndef ICOMPONENT
#define ICOMPONENT
	//Component interface
	class GameObject;
	class Collision2D;
	class GLENGINE_API IComponent
	{
	protected:
		GameObject* gameObjectPtr;
	public:
		virtual void Start();
		virtual void Update();
		virtual void OnDestroy();
		virtual void OnCollide(Collision2D* collision);
		IComponent();
		~IComponent();
		void OnAttached(GameObject* parentObject);
		GameObject* GetGameObject();
		Transform* GetTransform();
	};
#endif
}


