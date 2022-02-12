#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLEngine/Core/Transform.h"
namespace GLengine {
	Transform::Transform() {
		position = glm::vec3(0);
		rotation = glm::vec3(0);
		localScale = glm::vec3(1);
		worldUp = glm::vec3(0, 1, 0);
		up = glm::vec3(0, 1, 0);
		forward = glm::vec3(0, 0, -1);
		right = glm::vec3(1, 0, 0);
	}

	void Transform::Translate(glm::vec3 position) {
		this->position = position;
		UpdateVectors();
	}

	void Transform::Rotate(glm::vec3 rotation) {
		this->rotation = rotation;
		UpdateVectors();
	}

	void Transform::Scale(glm::vec3 scale) {
		this->localScale = scale;
		UpdateVectors();
	}

	glm::mat4 Transform::GetModelTransformationMatrix() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		model = glm::scale(model, localScale);

		return model;
	}

	void Transform::UpdateVectors() {
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		front.y = sin(glm::radians(rotation.x));
		front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		forward = glm::normalize(front);
		// also re-calculate the Right and Up vector
		right = glm::normalize(glm::cross(forward, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = glm::normalize(glm::cross(right, forward));
	}
}