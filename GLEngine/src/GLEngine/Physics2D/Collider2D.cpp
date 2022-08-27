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

	void BoxCollider2D::Start() {
		gizmoInstance = Gizmos::GetGizmoBoxInstance(GetTransform()->position, ((BoxBounds*)bounds)->worldSize, Color::Red());
	}

	void BoxCollider2D::Update() {
		Collider2D::Update();
		glm::vec2 boundsSize = ((BoxBounds*)bounds)->size;
		glm::vec3 locScale = GetTransform()->localScale;
		((BoxBounds*)bounds)->worldSize = glm::vec2(boundsSize.x* locScale.x, boundsSize.y * locScale.y);
	}

	void BoxCollider2D::OnDrawGizmo() {
		gizmoInstance->Draw();
	}

#pragma endregion

#pragma region CircleCollider2D
	CircleCollider2D::CircleCollider2D(float radius) {
		bounds = new CircleBounds();
		((CircleBounds*)bounds)->radius = radius;
	}

	void CircleCollider2D::Update() {
		Collider2D::Update();
		((CircleBounds*)bounds)->worldRadius = (((CircleBounds*)bounds)->radius * GetTransform()->localScale.x);
	}

	void CircleCollider2D::Start() {
		gizmoInstance = Gizmos::GetGizmoCircleInstance(GetTransform()->position, ((CircleBounds*)bounds)->worldRadius, Color::Red());
	}

	void CircleCollider2D::OnDrawGizmo() {
		gizmoInstance->Draw();
	}

#pragma endregion
}