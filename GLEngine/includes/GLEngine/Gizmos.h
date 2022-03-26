#pragma once
#include <GLEngine/Core/Core.h>
#include <GLEngine/Rendering.h>
#include <string>
#include <glm/glm.hpp>


namespace GLengine {

	struct GizmoPrimitive {
	public:
		GizmoPrimitive(float* vertices, int count);
		float* vertices;
		int count;
	};

	class GLENGINE_API GizmoPrimitives {
	public:
		static GizmoPrimitive* Box(glm::vec2 size);
		static GizmoPrimitive* Circle(float radius, int resolution);
	};

	class GLENGINE_API Gizmos {
		static std::string shaderId;
		static bool isInitialised;
		static Shader* gizmoShader;
		static void Init();
		static void DrawVertices(glm::vec3 position, float* vertices,int vertRows, glm::vec4 color);
	public:
		static void DrawBox(glm::vec2 centre, glm::vec2 size, glm::vec3 color);
		static void DrawCircle(glm::vec2 centre, float radius, glm::vec3 color);
	};
}