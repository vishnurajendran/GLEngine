#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Transform.h"
#include "Core.h"

namespace GLengine {
	class GLENGINE_API Camera {
		bool enabled = true;
		bool orthographic = false;
	public:
		int cameraID;
		float orthoSize = 1.0f;
		Transform transform;
		Camera(bool orthographic);
		~Camera();
		void SetEnabled(bool enabled);
		void UpdateCamera();
		bool IsEnabled();
		void SetToOrthographic(bool set);
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjection();
	};

	class GLENGINE_API ViewManager {
		static std::vector<Camera*> camerasInScene;
		static int internalCamNum;
	public:
		static int GetUniqueCameraID();
		static bool HasActiveCamera();
		static Camera* GetActiveCamera();
		static glm::mat4 GetViewMatrix();
		static glm::mat4 GetProjectionMatrix();
		static glm::mat4 GetOrthoProjection();
		static void AddToAvailableViews(Camera* camera);
		static void RemoveFromAvailableViews(Camera* camera);
		static void UpdateCameras();
	};
}