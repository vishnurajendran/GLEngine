#include<GLEngine/RenderCommand.h>
#include<GLEngine/OpenGL/OpenGLRendererAPI.h>

namespace GLengine {
	
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();

}