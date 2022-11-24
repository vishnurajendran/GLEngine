#include<GLEngine/Text/Font.h>
#include<GLEngine/Core/Component.h>

namespace GLengine {

	class GLENGINE_API TextComponent : public IComponent {
	private:
		Font* font = nullptr;
		RenderRequest* request = nullptr;

	public:
		TextComponent();
		void SetDefaultFont();
		void SetFont(std::string fontName, float pointSize);
		void SetText(std::string text);
		std::string GetText();
		void Update() override;
	};

}