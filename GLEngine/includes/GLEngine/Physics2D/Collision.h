#pragma once
#include <thread>
#include <vector>
#include <GLEngine/Physics2D/Collider2D.h>

namespace GLengine {
#ifndef COLLISION2D
#define COLLISION2D

	class GLENGINE_API Collision2D {
	public:
		Collider2D* thisCollider;
		Collider2D* other;
		Collision2D(Collider2D* thisCollider, Collider2D* other);
	};

	class CollisionManager {
		static int collisonChkFreq;
		static std::vector<Collider2D*> colliders;
		static std::thread collChkThread;
		static bool collisionDetectionActive;

		//Check collision between two colliders
		//CIRCLE - AABB
		static bool CheckCollision(CircleCollider2D* col1, BoxCollider2D* col2);

		//Check collision between two colliders
		//CIRCLE - CIRCLE
		static bool CheckCollision(CircleCollider2D* col1, CircleCollider2D* col2);

		//Check collision between two colliders
		//AABB - AABB
		static bool CheckCollision(BoxCollider2D* col1, BoxCollider2D* col2);

		static void CheckCollisions();

	public:
		//Add Colliders to collider list
		static void AddToColliders(Collider2D* col);

		//Remove Colliders to collider list
		static void RemoveFromColliders(Collider2D* col);

		//Check collision between two colliders
		static bool CheckCollisionAABB(Collider2D* col1, Collider2D* col2);

		//Start Collision check thread
		static void StartCollisionCheckThread();

		//Start Collision check thread
		static void StopCollisionCheckThread();
	};
#endif
}