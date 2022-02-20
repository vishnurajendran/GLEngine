#include "GLEngine/Core/Component.h"
#include "GLEngine/Core/GameObject.h"
#include "GLEngine/Debugging.h"
#include "GLEngine/Physics2D/Collision.h"

namespace GLengine {
	IComponent::IComponent() {
		this->Start();
	}

	void IComponent::OnAttached(GameObject* parentObject) {
		this->gameObjectPtr = parentObject;
	}

	GameObject* IComponent::GetGameObject() {
		return gameObjectPtr;
	}

	Transform* IComponent::GetTransform() {
		return &(gameObjectPtr->transform);
	}

	IComponent::~IComponent() {
		this->OnDestroy();
	}

	void IComponent::Start() {
		//default no op
	}

	void IComponent::Update() {
		//default no op
	}

	void IComponent::OnDestroy() {
		//default no op
	}

	void IComponent::OnCollide(Collision2D* col) {
		//default no op
	}
}