#pragma once
#include <map>
#include <vector>
#include <GLEngine/Core/Core.h>
#include <GLEngine/RendererAPI.h>
#include <GLEngine/Material.h>
#include <functional>

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
		bool dontDeleteRequestOnDraw = false;
		std::string name;
		VertexArray* vArray;
		Material* material;
		RendererAPI::RenderPrimitive drawPrimitive;
		int orderInLayer = 0;
		int nonIndexRows = 3;
		bool disposeVertsOnRender = false;
		bool disposeMatOnRender = false;
		RenderRequest(std::string name, VertexArray * vArray,Material* material, RendererAPI::RenderPrimitive drawPrimitive , int orderInLayer=0, bool disposeVertsOnRender=false, bool disposeMatOnRender=false, bool dontDeleteRequestOnDraw=false);
		inline void SetNonIndexedRowCount(int rows) { this->nonIndexRows = rows; };
		~RenderRequest();
	};

	class Renderer { 
	private:
		static bool initialised;
		static unsigned int renderFilter;
		static std::map<RenderLayer, std::vector<RenderRequest*>*> renderRequests;
		static void DoRenderRequest(RenderRequest* request);
		static void Initialise();
		static void Sort(std::vector<RenderRequest*>* requests);
		static void PushForRender(std::vector<RenderRequest*>* worldReuests, std::vector<RenderRequest*>* uiRequests, std::vector<RenderRequest*>* debugRequests);
		static void CleanRequests();
	public:
		static void Submit(RenderLayer layer, RenderRequest* request);
		static void Render();
		static inline int TotalInQueue() { 
			return	renderRequests.at(RenderLayer::World)->size() +
					renderRequests.at(RenderLayer::UI)->size() +
					renderRequests.at(RenderLayer::Debug)->size();
		}
	};

}

