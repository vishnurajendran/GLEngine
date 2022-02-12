#pragma once
#ifndef ICOMPONENT
#define ICOMPONENT

#include "Core.h"
#include "Transform.h"

namespace GLengine {
	//Component interface
	class GameObject;
	class GLENGINE_API IComponent
	{
	protected:
		GameObject* gameObjectPtr;
	public:
		virtual void Start();
		virtual void Update();
		virtual void OnDestroy();
		IComponent();
		~IComponent();
		void OnAttached(GameObject* parentObject);
		GameObject* GetGameObject();
		Transform* GetTransform();
	};
}

#endif
