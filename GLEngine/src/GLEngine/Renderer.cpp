#include <map>
#include <vector>
#include <thread>
#include <GLEngine/Renderer.h>
#include <GLEngine/RenderCommand.h>
#include <algorithm>
#include <GLEngine/Material.h>
#include <GLEngine/Debugging.h>

namespace GLengine {

	//Render request constructor
	RenderRequest::RenderRequest(std::string name, VertexArray* vArray, Material* material, RendererAPI::RenderPrimitive drawPrimitive, int orderInLayer, bool disposeVertsOnRender, bool disposeMatOnRender, bool dontDeleteRequestOnDraw) {
		this->name = name.c_str();
		this->vArray = vArray;
		this->material = material;
		this->drawPrimitive = drawPrimitive;
		this->orderInLayer = orderInLayer;
		this->disposeVertsOnRender = disposeVertsOnRender;
		this->disposeMatOnRender = disposeMatOnRender;
		this->dontDeleteRequestOnDraw = dontDeleteRequestOnDraw;
	}

	RenderRequest::~RenderRequest() {		
		if (disposeVertsOnRender) {
			VertexArray::Delete(vArray);
		}

		if (disposeMatOnRender)
		{
			delete material;
		}
	}

	bool Renderer::initialised = false;
	std::map<RenderLayer, std::vector<RenderRequest*>*> Renderer::renderRequests;

	void Renderer::DoRenderRequest(RenderRequest* request) {
		request->material->Use();
		request->vArray->Bind();

		if (request->vArray->GetIndexBuffer() == nullptr)
			RenderCommand::DrawNonIndexed(request->vArray, request->drawPrimitive, request->nonIndexRows);
		else
			RenderCommand::DrawIndexed(request->vArray, request->drawPrimitive);
		
		RenderCommand::EnableDepthTest(true);
		
		request->vArray->Unbind();
		request->material->Cleanup();
	}

	void Renderer::Initialise() {
		
		//add required layers
		renderRequests.insert({ RenderLayer::World, new std::vector<RenderRequest*>() });
		renderRequests.insert({ RenderLayer::UI, new std::vector<RenderRequest*>() });
		renderRequests.insert({ RenderLayer::Debug, new std::vector<RenderRequest*>() });

		initialised = true;
	}

	void Renderer::Submit(RenderLayer layer, RenderRequest* request) {
		if (!initialised) {
			Initialise();
		}

		renderRequests.at(layer)->push_back(request);
		Sort(renderRequests.at(layer));
	}

	void Renderer::CleanRequests() {
		for (auto req : *renderRequests.at(RenderLayer::World)) {
			if(!req->dontDeleteRequestOnDraw)
				delete req;
		}

		for (auto req : *renderRequests.at(RenderLayer::UI)) {
			if (!req->dontDeleteRequestOnDraw)
				delete req;
		}

		for (auto req : *renderRequests.at(RenderLayer::Debug)) {
			if (!req->dontDeleteRequestOnDraw)
				delete req;
		}

		renderRequests.at(RenderLayer::World)->clear();
		renderRequests.at(RenderLayer::UI)->clear();
		renderRequests.at(RenderLayer::Debug)->clear();
	}

	bool Compare(RenderRequest* req1, RenderRequest* req2) {
		return req1->orderInLayer < req2->orderInLayer;
	}

	void Renderer::Sort(std::vector<RenderRequest*>* requests) {
		std::sort(requests->begin(), requests->end(), Compare);
	}

	void Renderer::Render() {
		PushForRender(renderRequests.at(RenderLayer::World), renderRequests.at(RenderLayer::UI), renderRequests.at(RenderLayer::Debug));
		CleanRequests();
	}

	void Renderer::PushForRender(std::vector<RenderRequest*>* worldReuests, std::vector<RenderRequest*>* uiRequests, std::vector<RenderRequest*>* debugRequests) {
		
		for (auto req : *worldReuests) {
			DoRenderRequest(req);
		}

		for (auto req : *uiRequests) {
			RenderCommand::EnableDepthTest(false);
			DoRenderRequest(req);
			RenderCommand::EnableDepthTest(true);
		}
			
		for (auto req : *debugRequests) {
			RenderCommand::EnableDepthTest(false);
			DoRenderRequest(req);
			RenderCommand::EnableDepthTest(true);
		}
	}
}