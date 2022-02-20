#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
//GLFW
#include <GLFW/glfw3.h>

//engine
#include "GLEngine/Core/Core.h"
#include "GLEngine/Rendering.h"
#include "GLEngine/2D.h"
#include "GLEngine/Core/Time.h"
#include "GLEngine/Core/ViewManagement.h"
#include "GLEngine/Core/GameObject.h"
#include "GLEngine/Core/Preferences.h"
#include "GLEngine/Core/System.h"

//math
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//Phsyics2D
#include "GLEngine/Physics2D/Collision.h"

//other
#include <string>
#include "GLEngine/ResourceManager.h"
#include "GLEngine/InputHandling.h"
#include "GLEngine/Debugging.h"
#include "GLEngine/HelperDefinitions.h"

namespace GLengine {
class GLENGINE_API Engine {
	GLFWwindow* window;
	int engineHeight;
	int engineWidth;
	int preferredFPS;
	bool isFullscreen;
public:
	bool IsRunning();
	void Initialise(std::string applicationName, bool fullscreen, int height, int width, int fps);
	void Run();
	void Quit();
};
}
