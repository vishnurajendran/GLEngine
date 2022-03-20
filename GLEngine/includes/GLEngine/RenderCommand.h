#pragma once
#include<GLEngine/RendererAPI.h>
namespace GLengine {
	class RenderCommand {
	public:

		inline static void Clear() {
			rendererAPI->Clear();
		}

		inline static void ClearColor(glm::vec4 color) {
			rendererAPI->SetClearColor(color);
		}

		inline static void DrawIndexed(VertexArray* vArrray) {
			rendererAPI->DrawIndexed(vArrray);
		}

		inline static void Initialise() {
			rendererAPI->Initialise();
		}

	private:
		static RendererAPI* rendererAPI;
	};
}