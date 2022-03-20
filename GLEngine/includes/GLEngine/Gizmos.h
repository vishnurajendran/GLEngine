#pragma once
#include <GLEngine/Core/Core.h>
#include <GLEngine/Rendering.h>
#include <string>
#include <glm/glm.hpp>


namespace GLengine {
	class GLENGINE_API Gizmos {
		static std::string shaderId;
		static bool isInitialised;
		static Shader* gizmoShader;
		static void Init();
		static void DrawVertices(glm::vec3 position, float* vertices, int count,int vertRows, glm::vec4 color);
	public:
		static void DrawBox(glm::vec2 centre, glm::vec2 size, glm::vec3 color);
		static void DrawCircle(glm::vec2 centre, float radius, glm::vec3 color);
	};
}