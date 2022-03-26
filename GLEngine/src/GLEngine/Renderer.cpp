#include <GLEngine/Renderer.h>
#include <GLEngine/RenderCommand.h>

namespace GLengine {

	void Renderer::BeginScene() {
		//nothing for now
	}

	void Renderer::Submit(VertexArray* vArray, RendererAPI::RenderPrimitive drawPrimitive) {
		if (vArray->GetIndexBuffer() == nullptr)
			RenderCommand::DrawNonIndexed(vArray, drawPrimitive);
		else
			RenderCommand::DrawIndexed(vArray, drawPrimitive);
	}

	void Renderer::EndScene() {
		//nothing for now
	}

}