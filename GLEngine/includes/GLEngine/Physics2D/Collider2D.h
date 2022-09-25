#pragma once
#include <glm/glm.hpp>
#include <GLEngine/Core/Component.h>
#include <GLEngine/Gizmos.h>

namespace GLengine {
	class GLENGINE_API Bounds2D {
	public:
		glm::vec3 centre;
		glm::vec3 boundsScale;
		virtual bool InsideBounds(glm::vec3 pos) = 0;
		virtual void RecalculateBounds(glm::vec3 position, glm::vec3 scale) = 0;
	};

	class GLENGINE_API BoxBounds :public Bounds2D {
	public:
		glm::vec2 size = glm::vec2(0);
		glm::vec2 worldSize = glm::vec2(0);
		bool InsideBounds(glm::vec3 pos) override;
		void RecalculateBounds(glm::vec3 position, glm::vec3 scale) override;
	};

	class GLENGINE_API CircleBounds :public Bounds2D {
	public:
		float radius=0;
		float worldRadius = 0;
		bool InsideBounds(glm::vec3 pos) override;
		void RecalculateBounds(glm::vec3 position, glm::vec3 scale) override;
	};

	class GLENGINE_API Collider2D : public IComponent {
	protected:
		GizmoInstance* gizmoInstance;
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
		void Start() override;
		void Update() override;
		void OnDrawGizmo() override;
	};

	class GLENGINE_API CircleCollider2D :public Collider2D {
	public:
		CircleCollider2D(float radius);
		void Update() override;
		void Start() override;
		void OnDrawGizmo() override;
	};
}
