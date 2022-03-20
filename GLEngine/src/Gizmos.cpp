#include <GLEngine/Gizmos.h>
#include <GLEngine/ResourceManager.h>
#include <GLEngine/Core/ViewManagement.h>

namespace GLengine {

	bool Gizmos::isInitialised = false;
	std::string Gizmos::shaderId = "";
	Shader* Gizmos::gizmoShader;

	void Gizmos::Init() {
		isInitialised = true;
		shaderId = ResourceManager::CreateShader("Assets/Shaders/Gizmos/DefaultGizmo.shader");
		gizmoShader = ResourceManager::GetShader(shaderId);
	}

	void Gizmos::DrawVertices(glm::vec3 position, float* vertices, int count, int vertRows, glm::vec4 color) {
		
		if (!isInitialised)
			Init();
		
		//really stupid way to do
		//we are literally creating a buffer for each draw call.
		//should be ok for now.

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
		
		gizmoShader->UseShader();
		position.z += 0.15f;
		glm::mat4 view = ViewManager::GetViewMatrix();
		glm::mat4 projection = ViewManager::GetProjectionMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		view = glm::translate(view,position);

		gizmoShader->SetMatrix4f("model", glm::value_ptr(model));
		gizmoShader->SetMatrix4f("view", glm::value_ptr(view));
		gizmoShader->SetMatrix4f("projection", glm::value_ptr(projection));
		gizmoShader->SetUniform4f("lineColor", color);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP,0, vertRows);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Gizmos::DrawBox(glm::vec2 centre, glm::vec2 size, glm::vec3 color) {
		float* vert = new float[12]{
			//top left					
			-size.x/2,size.y/2,0,
			//top right
			 size.x/2,size.y/2, 0,
			//btm right									
			 size.x/2,-size.y/2, 0,	    
			//btm left
			-size.x/2,-size.y/2, 0,
		};

		DrawVertices(glm::vec3(centre,0), vert, 12,4, glm::vec4(color, 1));
		//std::thread t = std::thread{ DrawVertices,  };
	}

	void Gizmos::DrawCircle(glm::vec2 centre, float radius, glm::vec3 color) {

	}
}