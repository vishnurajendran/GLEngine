#include <GLEngine/Physics2D/Collider2D.h>
#include <GLEngine/Physics2D/Collision.h>
#include <GLEngine/Gizmos.h>

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
	}

	void BoxCollider2D::OnDrawGizmo() {
		Gizmos::DrawBox(GetTransform()->position, ((BoxBounds*)bounds)->size, glm::vec3(0, 1, 0));
	}

#pragma endregion

#pragma region CircleCollider2D
	CircleCollider2D::CircleCollider2D(float radius) {
		bounds = new CircleBounds();
		((CircleBounds*)bounds)->radius = radius;
	}

	void CircleCollider2D::OnDrawGizmo() {
		//need to add draw circle
	}

#pragma endregion
}