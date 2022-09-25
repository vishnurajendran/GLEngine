#include <GLEngine/Physics2D/Collider2D.h>
#include <GLEngine/Physics2D/Collision.h>
#include <GLEngine/Color.h>
#include <GLEngine/Gizmos.h>

namespace GLengine {

#pragma region Bounds
	bool BoxBounds::InsideBounds(glm::vec3 pos) {
		float xExtends = worldSize.x / 2;
		float yExtends = worldSize.y / 2;
		bool inX = pos.x > (centre.x - xExtends) && pos.x < (centre.x + xExtends);
		bool inY = pos.y > (centre.y - yExtends) && pos.y < (centre.y + yExtends);
		return inX && inY;
	}

	void BoxBounds::RecalculateBounds(glm::vec3 position, glm::vec3 scale) {
		centre = position;
		worldSize = glm::vec2(size.x * scale.x, size.y * scale.y);
		boundsScale = glm::vec3(size.x * scale.x, size.y * scale.y, scale.z);
	}

	bool CircleBounds::InsideBounds(glm::vec3 pos) {
		float distAbs = glm::abs(glm::distance(centre, pos));
		return distAbs < radius;
	}

	void CircleBounds::RecalculateBounds(glm::vec3 position, glm::vec3 scale) {
		centre = position;
		worldRadius = radius * scale.x;
		boundsScale = radius * scale;
	}

#pragma endregion

#pragma region Collider2D

	bool Collider2D::OverlapColliderAABB(Collider2D* other) {
		return CollisionManager::CheckCollisionAABB(this, other);
	}

	void Collider2D::Start() {
		CollisionManager::AddToColliders(this);
	}

	void Collider2D::Update() {
		bounds->centre = GetTransform()->position;
	}

	void Collider2D::OnDestroy() {
		CollisionManager::RemoveFromColliders(this);
	}

#pragma endregion

#pragma region BoxCollider2D

	BoxCollider2D::BoxCollider2D(glm::vec2 size) {
		bounds = new BoxBounds();
		((BoxBounds*)bounds)->size = size;
		((BoxBounds*)bounds)->worldSize = size;
	}

	void BoxCollider2D::Start() {
		Collider2D::Start();
		gizmoInstance = Gizmos::GetGizmoBoxInstance();
	}

	void BoxCollider2D::Update() {
		Collider2D::Update();
		bounds->RecalculateBounds(GetTransform()->position, GetTransform()->localScale);
		gizmoInstance->PrepareForDraw(GetTransform()->position, bounds->boundsScale, Color::White());
	}

	void BoxCollider2D::OnDrawGizmo() {
		Collider2D::OnDrawGizmo();
		gizmoInstance->Draw();
	}

#pragma endregion

#pragma region CircleCollider2D
	CircleCollider2D::CircleCollider2D(float radius) {
		bounds = new CircleBounds();
		((CircleBounds*)bounds)->radius = radius;
		((CircleBounds*)bounds)->worldRadius = radius;
	}

	void CircleCollider2D::Update() {
		Collider2D::Update();
		bounds->RecalculateBounds(GetTransform()->position,GetTransform()->localScale);
		gizmoInstance->PrepareForDraw(GetTransform()->position,bounds->boundsScale, Color::Yellow());
	}

	void CircleCollider2D::Start() {
		Collider2D::Start();
		gizmoInstance = Gizmos::GetGizmoCircleInstance();
	}

	void CircleCollider2D::OnDrawGizmo() {
		Collider2D::OnDrawGizmo();
		gizmoInstance->Draw();
	}

#pragma endregion
}