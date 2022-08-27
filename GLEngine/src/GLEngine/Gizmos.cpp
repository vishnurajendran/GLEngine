#include <GLEngine/Gizmos.h>
#include <GLEngine/ResourceManager.h>
#include <GLEngine/Core/ViewManagement.h>
#include <GLEngine/Renderer.h>

namespace GLengine {

	GizmoPrimitive::GizmoPrimitive(std::string name, float* vert, int count) {
		this->name = name;
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
		return new GizmoPrimitive("Box", vert, 12);
	}

	GizmoPrimitive* GizmoPrimitives::Circle(float radius, int resolution) {
		float* verts = new float[resolution * 3];
		int indx = 0;
		int baseIndex = 0;
		float angle = 0;
		float degToRad = 0.0174533;

		int adDelta = 0;

		for (int i = 0; i < resolution; i++)
		{
			float x = sin(degToRad * angle) * radius;
			float y = cos(degToRad * angle) * radius;

			verts[adDelta] = x;
			verts[adDelta + 1] = y;
			verts[adDelta + 2] = 0;

			adDelta += 3;

			angle += (360.0f / resolution);
		}

		return new GizmoPrimitive("Circle", verts, resolution * 3);
	}

	bool Gizmos::isInitialised = false;
	std::string Gizmos::shaderId = "";
	Shader* Gizmos::gizmoShader;

	void Gizmos::Init() {
		isInitialised = true;
		shaderId = ResourceManager::CreateShader("Assets/Shaders/Gizmos/DefaultGizmo.shader");
		gizmoShader = ResourceManager::GetShader(shaderId);
	}

	GizmoInstance* Gizmos::PrepareGizmoInstance(glm::vec3 position, GizmoPrimitive* primitive, glm::vec4 color) {
		
		if (!isInitialised)
			Init();
		
		VertexArray* vArray = VertexArray::Create();
		VertexBuffer* vBuffer = VertexBuffer::CreateBuffer(primitive->vertices, primitive->count);
		Material* gizmoMat = new Material(gizmoShader, nullptr, 0);
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position", false}
		};
		
		vBuffer->SetLayout(layout);
		vArray->AddVertexBuffer(vBuffer);
		glm::mat4 view = ViewManager::GetViewMatrix();
		glm::mat4 projection = ViewManager::GetProjectionMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		view = glm::translate(view,position);

		gizmoMat->SetMatrix4f("model", model);
		gizmoMat->SetMatrix4f("view", view);
		gizmoMat->SetMatrix4f("projection", projection);
		gizmoMat->SetUniform4f("lineColor", color);

		RenderRequest* request = new RenderRequest("Gizmo_" + primitive->name, vArray, gizmoMat, RendererAPI::RenderPrimitive::LINE_LOOP, 0, false, false, true);
		return new GizmoInstance(request);
	}

	GizmoInstance* Gizmos::GetGizmoBoxInstance(glm::vec2 centre, glm::vec2 size, Color* color) {
		GizmoPrimitive* boxPrimitive = GizmoPrimitives::Box(size);
		return PrepareGizmoInstance(glm::vec3(centre,0), boxPrimitive, color->GetVec4());
	}


	GizmoInstance* Gizmos::GetGizmoCircleInstance(glm::vec2 centre, float radius, Color* color) {
		GizmoPrimitive* circlePrimitive = GizmoPrimitives::Circle(radius, 50);
		return PrepareGizmoInstance(glm::vec3(centre, 0), circlePrimitive, color->GetVec4());
	}
}