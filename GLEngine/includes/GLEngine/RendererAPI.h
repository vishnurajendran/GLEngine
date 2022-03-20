#pragma once
#include<glm/glm.hpp>
#include<GLEngine/VertexArray.h>

namespace GLengine  {
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL,
		};

		virtual void Clear() = 0;
		virtual void Initialise() = 0;
		virtual void SetClearColor(glm::vec4 color) = 0;
		virtual void DrawIndexed(VertexArray* vArray) = 0;

		inline static API GetAPI() { return api; }
	private:
		static API api;
	};
}