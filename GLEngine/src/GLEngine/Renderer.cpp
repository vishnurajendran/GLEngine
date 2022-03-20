#include <GLEngine/Renderer.h>
#include <GLEngine/RenderCommand.h>

namespace GLengine {

	void Renderer::BeginScene() {
		//nothing for now
	}

	void Renderer::Submit(VertexArray* vArray) {
		RenderCommand::DrawIndexed(vArray);
	}

	void Renderer::EndScene() {
		//nothing for now
	}

}