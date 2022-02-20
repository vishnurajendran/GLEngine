#include <GLEngine/Physics2D/Collider2D.h>
#include <GLEngine/Physics2D/Collision.h>

namespace GLengine {

#pragma region Bounds
	bool BoxBounds::InsideBounds(glm::vec3 pos) {
		float xExtends = size.x / 2;
		float yExtends = size.y / 2;
		bool inX = pos.x > (centre.x - xExtends) && pos.x < (centre.x + xExtends);
		bool inY = pos.y > (centre.y - yExtends) && pos.y < (centre.y + yExtends);

		return inX && inY;
	}

	bool CircleBounds::InsideBounds(glm::vec3 pos) {
		float distAbs = glm::abs(glm::distance(centre, pos));
		return distAbs < radius;
	}
#pragma endregion

#pragma region Collider2D

	Collider2D::Collider2D() {
		bounds = new BoxBounds();
	}

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
		((BoxBounds*)bounds)->size = size;
	}
#pragma endregion

#pragma region CircleCollider2D
	CircleCollider2D::CircleCollider2D(float radius) {
		((CircleBounds*)bounds)->radius = radius;
	}
#pragma endregion
}