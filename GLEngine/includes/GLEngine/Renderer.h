#pragma once
#include <map>
#include <vector>
#include <GLEngine/Core/Core.h>
#include <GLEngine/RendererAPI.h>
#include <GLEngine/Material.h>

namespace GLengine {

	class GLENGINE_API RenderSettings {
	public:
		static inline RendererAPI::API GetRenderAPI() { return RendererAPI::GetAPI(); }
	};
	
	enum class RenderLayer {
		World = 0,
		UI,
		Debug
	};

	struct RenderRequest {
	public:
		std::string name;
		VertexArray* vArray;
		Material* material;
		RendererAPI::RenderPrimitive drawPrimitive;
		int orderInLayer = 0;
		RenderRequest(std::string name, VertexArray * vArray,Material* material, RendererAPI::RenderPrimitive drawPrimitive, int orderInLayer);
	};

	class Renderer { 
	private:
		static std::map<RenderLayer, std::vector<RenderRequest*>*>* renderRequests;
		static void DoRenderRequest(RenderRequest* request);
		static void Initialise();
		static void PostRender();
		static void PreRender();
	public:
		static void Submit(RenderLayer layer, RenderRequest* request);
		static void Render();
	};

}

