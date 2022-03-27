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

		inline static void DrawIndexed(VertexArray* vArrray, RendererAPI::RenderPrimitive drawPrimitive) {
			rendererAPI->DrawIndexed(vArrray, drawPrimitive);
		}

		inline static void DrawNonIndexed(VertexArray* vArrray, RendererAPI::RenderPrimitive drawPrimitive) {
			rendererAPI->DrawNonIndexed(vArrray, drawPrimitive);
		}

		inline static void EnableDepthTest(bool enable) {
			rendererAPI->EnableDepthTest(enable);
		}

		inline static void Initialise() {
			rendererAPI->Initialise();
		}

	private:
		static RendererAPI* rendererAPI;
	};
}