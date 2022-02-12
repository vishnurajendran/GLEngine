#include "GLEngine/Core/ViewManagement.h"
#include "GLEngine/Core/System.h"

#pragma region Camera Systems
namespace GLengine {
	Camera::Camera(bool orthographic = false) {
		cameraID = ViewManager::GetUniqueCameraID();
		this->orthographic = orthographic;
		ViewManager::AddToAvailableViews(this);
	}

	Camera::~Camera() {
		ViewManager::RemoveFromAvailableViews(this);
	}

	bool Camera::IsEnabled() {
		return enabled;
	}

	void Camera::SetEnabled(bool enabled) {
		this->enabled = enabled;
	}

	void Camera::UpdateCamera() {
		transform.UpdateVectors();
	}

	glm::mat4 Camera::GetViewMatrix() {
		return glm::lookAt(transform.position, transform.position + transform.forward, transform.up);
	}

	glm::mat4 Camera::GetProjection() {
		if (orthographic) {
			float scWidth = (float)ApplicationProperties::ScreenWidth;
			float scHeight = (float)ApplicationProperties::ScreenHeight;
			float ratio_size_per_depth = atan(glm::radians(45.0f / 2.0f) * 2.0f);
			auto distance = 1;
			float aspect = scWidth / scHeight;
			float size_y = ratio_size_per_depth * orthoSize;
			float size_x = ratio_size_per_depth * orthoSize * aspect;

			return glm::ortho(-size_x, size_x, -size_y, size_y, 0.0f, 2.0f * distance);
		}
		else
			return glm::perspective(glm::radians(45.0f), (float)ApplicationProperties::ScreenWidth / ApplicationProperties::ScreenHeight, 0.1f, 100.0f);
	}

	void Camera::SetToOrthographic(bool set) {
		orthographic = set;
	}

	bool operator==(const Camera& lhs, const Camera& rhs) {
		return lhs.cameraID == rhs.cameraID;
	}

#pragma endregion


#pragma region ViewManager

	std::vector<Camera*> ViewManager::camerasInScene;
	int ViewManager::internalCamNum = 0;

	int ViewManager::GetUniqueCameraID() {
		return internalCamNum++;
	}

	void ViewManager::AddToAvailableViews(Camera* camera) {
		camerasInScene.push_back(camera);
	}

	void ViewManager::RemoveFromAvailableViews(Camera* camera) {
		camerasInScene.erase(std::remove(camerasInScene.begin(), camerasInScene.end(), camera), camerasInScene.end());
	}

	void ViewManager::UpdateCameras() {
		for (Camera* camera : camerasInScene) {
			if (camera->IsEnabled())
				camera->UpdateCamera();
		}
	}

	bool ViewManager::HasActiveCamera() {
		for (Camera* camera : camerasInScene) {
			if (camera->IsEnabled())
				return true;
		}

		return false;
	}

	Camera* ViewManager::GetActiveCamera() {
		for (Camera* camera : camerasInScene) {
			if (camera->IsEnabled())
				return camera;
		}

		return NULL;
	}

	glm::mat4 ViewManager::GetViewMatrix() {
		for (Camera* camera : camerasInScene) {
			if (camera->IsEnabled())
				return camera->GetViewMatrix();
		}

		return glm::mat4(1); //return identity matrix
	}

	glm::mat4 ViewManager::GetProjectionMatrix() {
		for (Camera* camera : camerasInScene) {
			if (camera->IsEnabled())
				return camera->GetProjection();
		}

		return glm::mat4(1); //return identity matrix
	}
}
#pragma endregion