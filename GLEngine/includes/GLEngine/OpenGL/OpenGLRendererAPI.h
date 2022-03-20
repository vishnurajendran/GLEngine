#pragma once
#include<GLEngine/RendererAPI.h>
namespace GLengine {
	class OpenGLRendererAPI :public RendererAPI {
	public:
		void Clear() override;
		void Initialise() override;
		void SetClearColor(glm::vec4 color) override;
		void DrawIndexed(VertexArray* vArray) override;
	};
}