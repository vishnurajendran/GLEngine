#include <map>
#include <vector>
#include <GLEngine/Renderer.h>
#include <GLEngine/RenderCommand.h>
#include <algorithm>
#include <GLEngine/Material.h>
#include <GLEngine/Debugging.h>

namespace GLengine {

	//Render request constructor
	RenderRequest::RenderRequest(std::string name, VertexArray* vArray, Material* material,RendererAPI::RenderPrimitive drawPrimitive, int orderInLayer = 0) {
		this->name = name;
		this->vArray = vArray;
		this->material = material;
		this->drawPrimitive = drawPrimitive;
		this->orderInLayer = orderInLayer;
	}
	
	std::map<RenderLayer, std::vector<RenderRequest*>*>* Renderer::renderRequests = nullptr;

	void Renderer::DoRenderRequest(RenderRequest* request) {
		request->material->Use();
		request->vArray->Bind();

		if (request->vArray->GetIndexBuffer() == nullptr)
			RenderCommand::DrawNonIndexed(request->vArray, request->drawPrimitive);
		else
			RenderCommand::DrawIndexed(request->vArray, request->drawPrimitive);
		
		RenderCommand::EnableDepthTest(true);

		request->vArray->Unbind();
		request->material->Cleanup();
	}

	bool Compare(RenderRequest* req1, RenderRequest* req2) {
		return req1->orderInLayer < req2->orderInLayer;
	}

	void Renderer::PreRender() {
		//do things that is needed to setup render tasks
		// for now we sort the layers here according to sorting layer
		std::sort(renderRequests->at(RenderLayer::World)->begin(), renderRequests->at(RenderLayer::World)->end(), Compare);
		std::sort(renderRequests->at(RenderLayer::UI)->begin(), renderRequests->at(RenderLayer::UI)->end(), Compare);
		std::sort(renderRequests->at(RenderLayer::Debug)->begin(), renderRequests->at(RenderLayer::Debug)->end(), Compare);
	}

	void Renderer::Initialise() {
		renderRequests = new std::map<RenderLayer, std::vector<RenderRequest*>*>();

		//add required layers
		renderRequests->insert({ RenderLayer::World, new std::vector<RenderRequest*>() });
		renderRequests->insert({ RenderLayer::UI, new std::vector<RenderRequest*>() });
		renderRequests->insert({ RenderLayer::Debug, new std::vector<RenderRequest*>() });
	}

	void Renderer::Submit(RenderLayer layer, RenderRequest* request) {
		if (renderRequests == nullptr) {
			Initialise();
		}

		renderRequests->at(layer)->push_back(request);
	}

	void Renderer::PostRender() {
		//cleanup things after render
		//for now remove all completed requests
		for (auto item : *renderRequests->at(RenderLayer::World)) {
			delete(item);
		}
		renderRequests->at(RenderLayer::World)->clear();

		for (auto item : *renderRequests->at(RenderLayer::UI)) {
			delete(item);
		}
		renderRequests->at(RenderLayer::UI)->clear();

		for (auto item : *renderRequests->at(RenderLayer::Debug)) {
			delete(item);
		}
		renderRequests->at(RenderLayer::Debug)->clear();
		
	}

	void Renderer::Render() {
		
		PreRender();
		//render in order
		//World -> UI -> Debug

		for (auto item : *renderRequests->at(RenderLayer::World)) {
			DoRenderRequest(item);
		}
		for (auto item : *renderRequests->at(RenderLayer::UI)) {
			RenderCommand::EnableDepthTest(false);
			DoRenderRequest(item);
			RenderCommand::EnableDepthTest(true);
		}
		for (auto item : *renderRequests->at(RenderLayer::Debug)) {
			RenderCommand::EnableDepthTest(false);
			DoRenderRequest(item);
			RenderCommand::EnableDepthTest(true);
		}

		PostRender();
	}
}