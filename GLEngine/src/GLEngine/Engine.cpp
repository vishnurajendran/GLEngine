#pragma once
#include "GLEngine/Engine.h"

namespace GLengine {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		if (width <= 0 || height <= 0)
			return;

		glViewport(0, 0, width, height);
		ApplicationProperties::ScreenHeight = height;
		ApplicationProperties::ScreenWidth = width;
	}

	void Engine::Initialise(std::string applicationName, bool fullscreen, int height, int width, int fps) {

		Debug::StartLogger();
		AddSection("Engine Init");

		LogInfo("Initialising GLFW");
		if (!glfwInit()) {
			LogError("Failed Initialising GLFW");
			CloseSection();
			return;
		}

		LogInfo((std::string("Creating Window for ") + applicationName).c_str());
		//Getting primary monitor
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		this->preferredFPS = fps <= 0 ? mode->refreshRate : fps;
		this->engineHeight = height <= 0 ? mode->height : height;
		this->engineWidth = width <= 0 ? mode->width : width;
		this->isFullscreen = fullscreen;

		ApplicationProperties::FPS = preferredFPS;
		ApplicationProperties::ScreenHeight = engineHeight;
		ApplicationProperties::ScreenWidth = engineWidth;
		ApplicationProperties::IsFullscreen = isFullscreen;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, preferredFPS);

		//creating OpenGL Window
		window = glfwCreateWindow(engineWidth, engineHeight, applicationName.c_str(), isFullscreen ? monitor : NULL, NULL);

		if (!window) {
			LogError("Failed Creating Window");
			CloseSection();
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		//loading OpenGL function loader
		LogInfo("Loading GLAD");
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LogError("Failed to initialize GLAD");;
			CloseSection();
			return;
		}

		Input::Init(window);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		LogInfo("Enigne Ready");
		CloseSection();
		AddSection(" Runtime ");
	}

	void Engine::Run() {

		Time::Update();
		glfwPollEvents();

		glfwSwapBuffers(window);

		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!ViewManager::HasActiveCamera()) {
			LogWarning("No active cameras detected");
			return;
		}

		GameObjectManager::UpdateGameObjects();
	}

	void Engine::Quit() {
		CloseSection();
		AddSection(" Engine Cleanup ");
		LogInfo("Enigne Shutdown initiated");
		glfwDestroyWindow(window);
		glfwTerminate();
		GameObjectManager::Cleanup();
		ResourceManager::CleanAll();
		LogInfo("Enigne Shutting down");
		CloseSection();
	}

	bool Engine::IsRunning() {
		return !glfwWindowShouldClose(window);
	}
}