#include <GLEngine/Text/TextComponent.h>
#include <GLEngine/Core/ViewManagement.h>
#include <GLEngine/Color.h>

namespace GLengine {

	TextComponent::TextComponent() {
		Debug::Log("Text Component Init");
		request = nullptr;
		SetDefaultFont();
	}

	void TextComponent::SetDefaultFont() {
		Debug::Log("Setting default font (arial.ttf @ 1)");
		SetFont("arial.ttf", 1);
	}

	void TextComponent::SetText(std::string text) {

		if (font == nullptr) {
			SetDefaultFont();
		}

		//only update this only, if the text changes.
		glm::vec3 pos = GetTransform()->position;
		glm::vec3 scale = GetTransform()->localScale;

		/*if (request != nullptr)
			delete request;*/

		request = font->GetTextRenderRequest(text, 0, 0, 1, 1);
		Debug::Log("Text Set");
	}

	std::string TextComponent::GetText() {
		return "GG";
	}

	void TextComponent::SetFont(std::string fontName, float pointSize) {

		/*if (font != nullptr) {
			Debug::Log("Deleting previous font data");
			delete font;
		}*/

		font = new Font(fontName, pointSize);
		Debug::Log("Font Set");
	}

	void TextComponent::Update() {
		if (request == nullptr)
			return;

		glm::mat4 view = ViewManager::GetViewMatrix();
		glm::mat4 projection = ViewManager::GetProjectionMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		glm::vec3 pos = GetTransform()->position;
		glm::vec3 scale = GetTransform()->localScale;

		model = glm::scale(model, scale);
		view = glm::translate(view, pos);

		request->material->SetMatrix4f("model", model);
		request->material->SetMatrix4f("view", view);
		request->material->SetMatrix4f("projection", projection);
		request->material->SetUniform4f("lineColor", Color::White()->GetVec4());

		Renderer::Submit(RenderLayer::UI, request);
	}
}