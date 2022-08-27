#pragma once
#include <GLEngine/Core/Core.h>
#include <GLEngine/Rendering.h>
#include <GLEngine/Color.h>
#include <string>
#include <glm/glm.hpp>
#include <GLEngine/Renderer.h>


namespace GLengine {

	struct GizmoPrimitive {
	public:
		GizmoPrimitive(std::string name, float* vertices, int count);
		std::string name;
		float* vertices;
		int count;
	};

	class GizmoInstance {
		RenderRequest* request;
	public:
		inline GizmoInstance(RenderRequest* request) { this->request = request; }
		inline ~GizmoInstance() { delete request; }
		inline void Destroy() { delete this; }
		inline void Draw() {
			Renderer::Submit(RenderLayer::Debug, request);
		}
	};

	class GizmoPrimitives {
	public:
		static GizmoPrimitive* Box(glm::vec2 size);
		static GizmoPrimitive* Circle(float radius, int resolution);
	};

	class GLENGINE_API Gizmos {
		static std::string shaderId;
		static bool isInitialised;
		static Shader* gizmoShader;
		static void Init();
		static GizmoInstance* PrepareGizmoInstance(glm::vec3 position,GizmoPrimitive* primitive, glm::vec4 color);
	public:
		static GizmoInstance* GetGizmoBoxInstance(glm::vec2 centre, glm::vec2 size, Color* color);
		static GizmoInstance* GetGizmoCircleInstance(glm::vec2 centre, float radius, Color* color);
	};
}