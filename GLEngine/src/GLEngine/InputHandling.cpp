#include <glm/glm.hpp>
#include "GLEngine/InputHandling.h"
#include<GLFW/glfw3.h>

namespace GLengine {

	bool Input::inputKeyArr[1024];

	void Input::Init(GLFWwindow* window) {
		glfwSetKeyCallback(window, Input::key_callback);
	}

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) {
				inputKeyArr[key] = true;
			}
			else if (action == GLFW_RELEASE) {
				inputKeyArr[key] = false;
			}
		}
	}

	glm::vec2 Input::GetInputVector() {
		glm::vec2 input = glm::vec2(0);
		if (IsKeyPressed(KeyCode::key_w) || IsKeyPressed(KeyCode::key_up)) {
			input.y = 1;
		}
		else if (IsKeyPressed(KeyCode::key_s) || IsKeyPressed(KeyCode::key_down)) {
			input.y = -1;
		}

		if (IsKeyPressed(KeyCode::key_a) || IsKeyPressed(KeyCode::key_left)) {
			input.x = -1;
		}
		else if (IsKeyPressed(KeyCode::key_d) || IsKeyPressed(KeyCode::key_right)) {
			input.x = 1;
		}
		return input;
	}

	bool Input::IsKeyPressed(KeyCode keyCode) {
		return inputKeyArr[keyCode];
	}
};
