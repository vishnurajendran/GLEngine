#pragma once
#include <GLEngine/Core/Core.h>
#include <GLEngine/RendererAPI.h>

namespace GLengine {

	class GLENGINE_API RenderSettings {
	public:
		static inline RendererAPI::API GetRenderAPI() { return RendererAPI::GetAPI(); }
	};

	class Renderer {
	public:
		static void BeginScene();
		static void Submit(VertexArray* vArray, RendererAPI::RenderPrimitive drawPrimitive= RendererAPI::RenderPrimitive::TRIANGLES);
		static void EndScene();
	};

}

