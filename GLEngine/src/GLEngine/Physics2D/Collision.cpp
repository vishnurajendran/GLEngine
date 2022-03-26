#pragma once
#include <GLEngine/Core/GameObject.h>
#include <GLEngine/Physics2D/Collision.h>
#include <GLEngine/Debugging.h>
#include <chrono>

namespace GLengine {
	std::vector<Collider2D*> CollisionManager::colliders;
	bool CollisionManager::collisionDetectionActive = false;
	std::thread CollisionManager::collChkThread;
	int CollisionManager::collisonChkFreq = 60;

	Collision2D::Collision2D(Collider2D* thisCollider, Collider2D* other) {
		this->thisCollider = thisCollider;
		this->other = other;
	}

	void CollisionManager::AddToColliders(Collider2D* col) {
		colliders.push_back(col);
		LogInfo(("[ Collision Manager ] total colliders " + std::to_string(colliders.size())).c_str());
	}

	void CollisionManager::RemoveFromColliders(Collider2D* col) {
		colliders.erase(std::remove(colliders.begin(), colliders.end(), col), colliders.end());
	}

	bool CollisionManager::CheckCollision(BoxCollider2D* col1, BoxCollider2D* col2) {

		BoxBounds* b1 = (BoxBounds*)col1->bounds;
		BoxBounds* b2 = (BoxBounds*)col2->bounds;

		//collision x-axis
		bool collisionX = (b1->centre.x + b1->worldSize.x) >= b2->centre.x &&
						  (b2->centre.x + b2->worldSize.x) >= b1->centre.x;

		// collision y-axis?
		bool collisionY = (b1->centre.y + b1->worldSize.y) >= b2->centre.y &&
						  (b2->centre.y + b2->worldSize.y) >= b1->centre.y;

		// collision only if on both axes
		return collisionX && collisionY;
	}

	bool CollisionManager::CheckCollision(CircleCollider2D* col1, CircleCollider2D* col2) {
		float dist = glm::abs(glm::distance(col1->bounds->centre, col2->bounds->centre));
		bool colliding = dist <= (((CircleBounds*)col1->bounds)->worldRadius + ((CircleBounds*)col2->bounds)->worldRadius);
		return colliding;
	}

	bool CollisionManager::CheckCollision(CircleCollider2D* col1, BoxCollider2D* col2) {
		BoxBounds* b = (BoxBounds*)col2->bounds;
		CircleBounds* c = (CircleBounds*)col1->bounds;
		
		// get center point circle first 
		glm::vec2 center(col1->GetTransform()->position + c->worldRadius);
		// calculate AABB info (center, half-extents)
		glm::vec2 aabb_half_extents(b->worldSize.x / 2.0f, b->worldSize.y / 2.0f);
		glm::vec2 aabb_center(
			col1->GetTransform()->position.x + aabb_half_extents.x,
			col1->GetTransform()->position.y + aabb_half_extents.y
		);
		// get difference vector between both centers
		glm::vec2 difference = center - aabb_center;
		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		// add clamped value to AABB_center and we get the value of box closest to circle
		glm::vec2 closest = aabb_center + clamped;
		// retrieve vector between center circle and closest point AABB and check if length <= radius
		difference = closest - center;
		return glm::length(difference) < c->worldRadius;
	}

	bool CollisionManager::CheckCollisionAABB(Collider2D* col1, Collider2D* col2){
		
		if (dynamic_cast<BoxCollider2D*>(col1) != nullptr && dynamic_cast<BoxCollider2D*>(col2) != nullptr) {
			return CheckCollision((BoxCollider2D*)col1, (BoxCollider2D*)col2);
		}
		else if (dynamic_cast<CircleCollider2D*>(col1) != nullptr && dynamic_cast<BoxCollider2D*>(col2) != nullptr) {
			return CheckCollision((CircleCollider2D*)col2, (BoxCollider2D*)col1);
		}
		else if (dynamic_cast<BoxCollider2D*>(col1) != nullptr && dynamic_cast<CircleCollider2D*>(col2) != nullptr) {
			return CheckCollision((CircleCollider2D*)col1, (BoxCollider2D*)col2);
		}
		else if (dynamic_cast<CircleCollider2D*>(col1) != nullptr && dynamic_cast<CircleCollider2D*>(col2) != nullptr) {
			return CheckCollision((CircleCollider2D*)col1, (CircleCollider2D*)col2);
		}
	}

	void CollisionManager::StartCollisionCheckThread() {
		LogInfo("[ Collision Manager ] Starting collision detection");
		collisionDetectionActive = true;
		collChkThread = std::thread{ CheckCollisions };
	}

	void CollisionManager::StopCollisionCheckThread() {
		if (!collisionDetectionActive)
			return;

		LogInfo("[ Collision Manager ] Stopping collision detection");
		collisionDetectionActive = false;
		collChkThread.join();
	}

	void CollisionManager::CheckCollisions() {
		long waitPeriod = (1.0f / collisonChkFreq)*1000;
		LogInfo("[ Collision Manager ] Collision detection started");
		while (collisionDetectionActive) {
			
			if (colliders.size() <= 1)
				continue;

			for (int i = 0; i < colliders.size() - 1; i++) {
				for (int j = i+1; j < colliders.size(); j++) {
					if (CheckCollisionAABB(colliders[i], colliders[j])) {
						GameObject* g1 = colliders[i]->GetGameObject();
						GameObject* g2 = colliders[j]->GetGameObject();

						Collision2D* g1Colision = new Collision2D(colliders[i], colliders[j]);
						Collision2D* g2Colision = new Collision2D(colliders[j], colliders[i]);
						g1->SendOnCollideEventToComponents(g1Colision);
						g2->SendOnCollideEventToComponents(g2Colision);
					}
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(waitPeriod));
		}
	}
}