#include<GLEngine/OpenGL/OpenGLRendererAPI.h>
#include<glad/glad.h>

namespace GLengine {
	
	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(glm::vec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Initialise() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::DrawIndexed(VertexArray* vArray) {
		glDrawElements(GL_TRIANGLES, vArray->GetIndexBuffer()->GetLength(), GL_UNSIGNED_INT, nullptr);
	}
}