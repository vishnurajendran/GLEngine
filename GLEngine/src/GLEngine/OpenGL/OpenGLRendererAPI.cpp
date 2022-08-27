#include<GLEngine/OpenGL/OpenGLRendererAPI.h>
#include<glad/glad.h>
#include <GLEngine/Debugging.h>

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

	void OpenGLRendererAPI::EnableDepthTest(bool enable) {
		if (enable)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	GLenum GetGLDrawPrimitive(RendererAPI::RenderPrimitive primitive) {
		switch (primitive) {
		case RendererAPI::RenderPrimitive::TRIANGLES:
			return GL_TRIANGLES;

		case RendererAPI::RenderPrimitive::LINES:
			return GL_LINES;

		case RendererAPI::RenderPrimitive::LINE_LOOP:
			return GL_LINE_LOOP;
		}
	}

	void OpenGLRendererAPI::DrawIndexed(VertexArray* vArray, RenderPrimitive drawPrimitive) {
		GLenum primitive = GetGLDrawPrimitive(drawPrimitive);
		glDrawElements(primitive, vArray->GetIndexBuffer()->GetLength(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawNonIndexed(VertexArray* vArray, RenderPrimitive drawPrimitive, int rows) {
		GLenum primitive = GetGLDrawPrimitive(drawPrimitive);
		glDrawArrays(primitive, 0, vArray->GetVertexBuffers()[0]->GetLength()/rows);
	}
}