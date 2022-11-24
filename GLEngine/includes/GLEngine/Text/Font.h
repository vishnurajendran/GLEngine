#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <string>
#include <GLEngine/Texture2D.h>
#include <GLEngine/Renderer.h>

namespace GLengine {

	struct CharacterInfo {
		float ax = 0; // advance.x
		float ay = 0; // advance.y

		float bw = 0; // bitmap.width;
		float bh = 0; // bitmap.rows;

		float bl = 0; // bitmap_left;
		float bt = 0; // bitmap_top;

		float tx = 0; // x offset of glyph in texture coordinates
	};

	class Font {
	private:
		const std::string CONST_PATH = "Assets/Fonts/";
		bool initialised = false;

		FT_Library ft;
		FT_Face face;

		std::vector<CharacterInfo*>* characters;

		//atlas data
		Texture2D* atlas = nullptr;
		int atlasWidth = 0;
		int atlasHeight = 0;

		float fontSize = 0.0f;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance = 0;


		void LoadFontAtlas();
	public:
		Font(std::string fontFamily, float fontSize);
		~Font();
		RenderRequest* GetTextRenderRequest(std::string text, float x, float y, float sx, float sy);
	};

}