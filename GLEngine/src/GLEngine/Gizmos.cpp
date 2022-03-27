#include <GLEngine/Gizmos.h>
#include <GLEngine/ResourceManager.h>
#include <GLEngine/Core/ViewManagement.h>
#include <GLEngine/Renderer.h>

namespace GLengine {

	GizmoPrimitive::GizmoPrimitive(float* vert, int count) {
		this->vertices = vert;
		this->count = count;
	}

	GizmoPrimitive* GizmoPrimitives::Box(glm::vec2 size) {
		float* vert = new float[12]{
			//top left					
			-0.5f * size.x,0.5f * size.y,0,
			//top right
			 0.5f * size.x,0.5f * size.y, 0,
			 //btm right									
			 0.5f * size.x,-0.5f * size.y, 0,
			 //btm left
			 -0.5f * size.x,-0.5f * size.y, 0,
		};
		return new GizmoPrimitive(vert, 12);
	}

	GizmoPrimitive* GizmoPrimitives::Circle(float radius, int resolution) {
		float* verts = new float[resolution * 3];
		int indx = 0;
		int baseIndex = 0;
		float angle = 0;
		float degToRad = 0.0174533;

		int adDelta = 0;

		for (int i = 0; i < (resolution + 1); i++)
		{
			float x = sin(degToRad * angle) * radius;
			float y = cos(degToRad * angle) * radius;

			verts[adDelta] = x;
			verts[adDelta + 1] = y;
			verts[adDelta + 2] = 0;

			adDelta += 3;

			angle += (360.0f / resolution);
		}

		return new GizmoPrimitive(verts, resolution * 3);
	}

	bool Gizmos::isInitialised = false;
	std::string Gizmos::shaderId = "";
	Shader* Gizmos::gizmoShader;
	glm::vec4 Gizmos::gizmoColor;

	void Gizmos::Init() {
		isInitialised = true;
		gizmoColor = glm::vec4(0, 1, 0,0);
		shaderId = ResourceManager::CreateShader("Assets/Shaders/Gizmos/DefaultGizmo.shader");
		gizmoShader = ResourceManager::GetShader(shaderId);
	}

	void Gizmos::DrawVertices(glm::vec3 position, float* vertices, int count, glm::vec4 color) {
		
		if (!isInitialised)
			Init();
		
		VertexArray* vArray = VertexArray::Create();
		VertexBuffer* vBuffer = VertexBuffer::CreateBuffer(vertices, count);
		Material* gizmoMat = new Material(gizmoShader, nullptr, 0);
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Positiont", false}
		};
		
		vBuffer->SetLayout(layout);
		vArray->AddVertexBuffer(vBuffer);
		//position.z += 0.15f;
		glm::mat4 view = ViewManager::GetViewMatrix();
		glm::mat4 projection = ViewManager::GetProjectionMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		view = glm::translate(view,position);

		gizmoMat->SetMatrix4f("model", model);
		gizmoMat->SetMatrix4f("view", view);
		gizmoMat->SetMatrix4f("projection", projection);
		gizmoMat->SetUniform4f("lineColor", color);

		Renderer::Submit(RenderLayer::Debug, new RenderRequest("Gizmo",vArray,gizmoMat, RendererAPI::RenderPrimitive::LINE_LOOP, 0));
	}

	void Gizmos::SetGizmoColor(glm::vec4 color) {
		gizmoColor = color;
		gizmoColor.a = 1;
	}

	void Gizmos::DrawBox(glm::vec2 centre, glm::vec2 size) {
		
		GizmoPrimitive* boxPrimitive = GizmoPrimitives::Box(size);
		DrawVertices(glm::vec3(centre,0), boxPrimitive->vertices, boxPrimitive->count, gizmoColor);
	}

	void Gizmos::DrawCircle(glm::vec2 centre, float radius) {
		GizmoPrimitive* boxPrimitive = GizmoPrimitives::Circle(radius, 50);
		DrawVertices(glm::vec3(centre, 0), boxPrimitive->vertices, boxPrimitive->count, gizmoColor);
	}
}