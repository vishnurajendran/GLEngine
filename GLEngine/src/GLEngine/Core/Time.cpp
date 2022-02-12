#include <GLFW/glfw3.h>
#include "GLEngine/Core/Time.h"
namespace GLengine {
    float Time::deltaTime = 0.0f;
    float Time::time = 0.0f;
    float Time::lastFrameTime = 0.0f;

    void Time::Update() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;

        time = glfwGetTime();
    }
}