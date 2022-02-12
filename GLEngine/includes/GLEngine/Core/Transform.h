#pragma once
#include <glm/glm.hpp>
#include "Core.h"

namespace GLengine {
	class GLENGINE_API Transform {

	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 localScale;

		glm::vec3 worldUp;
		glm::vec3 up;
		glm::vec3 forward;
		glm::vec3 right;

		Transform();
		void UpdateVectors();
		glm::mat4 GetModelTransformationMatrix();
		void Translate(glm::vec3 position);
		void Rotate(glm::vec3 rotation);
		void Scale(glm::vec3 scale);
	};
}