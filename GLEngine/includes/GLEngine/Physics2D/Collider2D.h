#pragma once
#include <glm/glm.hpp>
#include <GLEngine/Core/Component.h>

namespace GLengine {
	class GLENGINE_API Bounds2D {
	public:
		glm::vec3 centre;
		virtual bool InsideBounds(glm::vec3 pos) = 0;
	};

	class GLENGINE_API BoxBounds :public Bounds2D {
	public:
		glm::vec2 size = glm::vec2(0);
		glm::vec2 worldSize = glm::vec2(0);
		bool InsideBounds(glm::vec3 pos) override;
	};

	class GLENGINE_API CircleBounds :public Bounds2D {
	public:
		float radius=0;
		float worldRadius = 0;
		bool InsideBounds(glm::vec3 pos) override;
	};

	class GLENGINE_API Collider2D : public IComponent {
	public:
		Bounds2D* bounds;
		virtual void Start();
		virtual void Update();
		virtual void OnDestroy();
		virtual bool OverlapColliderAABB(Collider2D* other);
	};

	class GLENGINE_API BoxCollider2D :public Collider2D {
	public:
		BoxCollider2D(glm::vec2 size);
		void Update();
		void OnDrawGizmo();
	};

	class GLENGINE_API CircleCollider2D :public Collider2D {
	public:
		CircleCollider2D(float radius);
		void Update();
		void OnDrawGizmo();
	};
}
