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
		
		void PrepareForDraw(glm::vec3 position, glm::vec3 scale, Color* color);
		inline void Draw() {
			Renderer::Submit(RenderLayer::Debug, request);
		}
		
		inline void Destroy() { delete this; }
	};

	class GizmoPrimitives {
	public:
		static GizmoPrimitive* Box();
		static GizmoPrimitive* Circle(int resolution);
	};

	class GLENGINE_API Gizmos {
		static std::string shaderId;
		static bool isInitialised;
		static Shader* gizmoShader;
		static void Init();
		static GizmoInstance* PrepareGizmoInstance(GizmoPrimitive* primitive);
	public:
		static GizmoInstance* GetGizmoBoxInstance();
		static GizmoInstance* GetGizmoCircleInstance();
	};
}