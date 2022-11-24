#include <GLengine/Text/Font.h>
#include <GLEngine/Debugging.h>
#include <GLEngine/ResourceManager.h>
#include <GLEngine/Renderer.h>
#include <GLEngine/Core/ViewManagement.h>
#include<algorithm>
#include<string>

namespace GLengine {
	Font::Font(std::string fontFamily, float fontSize) {
		ft = nullptr;
		face = nullptr;
		atlas = nullptr;
		bearing = glm::ivec2(0, 0);
		size = glm::ivec2(0, 0);
		characters = new std::vector<CharacterInfo*>();
		for (int i = 0; i < 128; i++) {
			characters->push_back (new CharacterInfo{ 0,0,0,0,0,0,0 });
		}

		std::string path = CONST_PATH + fontFamily;
		if (FT_Init_FreeType(&ft))
		{
			Debug::LogError("ERROR::FREETYPE: Could not init FreeType Library");
			return;
		}

		if (FT_New_Face(ft, path.c_str(), 0, &face))
		{
			Debug::LogError("ERROR::FREETYPE: Failed to load font");
			return;
		}

		this->fontSize = fontSize;
		Debug::Log("Generating Atlas");
		LoadFontAtlas();
		Debug::Log("Generation Complete");
		initialised = true;

	}

	Font::~Font() {
		Debug::Log("Font deleted");
	}

	void Font::LoadFontAtlas() {
		FT_Set_Pixel_Sizes(face, 0, fontSize);
		FT_GlyphSlot g = face->glyph;

		atlasWidth =  0;
		atlasHeight = 0;
	
		for (int i = 32; i < 128; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				fprintf(stderr, "Loading character %c failed!\n", i);
				continue;
			}

			atlasWidth += g->bitmap.width;
			atlasHeight = std::max(atlasHeight, (int)g->bitmap.rows);
		}

		//create our texture
		auto id = ResourceManager::CreateEmptyTexture2D(atlasWidth, atlasHeight, TextureFormat::RED, TextureWrap::BorderClamp);
		atlas = ResourceManager::GetTexture2D(id);

		//Fill it now :p
		atlas->Bind();
		int x = 0;
		for (int i = 32; i < 128; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER))
				continue;

			atlas->SetTexturePixels(g->bitmap.buffer, x, 0, g->bitmap.width, g->bitmap.rows);
			characters->at(i)->ax = g->advance.x >> 6;
			characters->at(i)->ay = g->advance.y >> 6;

			characters->at(i)->bw = g->bitmap.width;
			characters->at(i)->bh = g->bitmap.rows;

			characters->at(i)->bl = g->bitmap_left;
			characters->at(i)->bt = g->bitmap_top;
			characters->at(i)->tx = (float)x / atlasWidth;
			x += g->bitmap.width;

		}
	}

	void CopyToArray(float* arrayTarget, float* arraySource, int offset, int size) {
		for (int i = 0; i < size; i++) {
			arrayTarget[offset + i] = arraySource[i];
		}
	}

	RenderRequest* Font::GetTextRenderRequest(std::string text, float x, float y, float sx, float sy) {
		float* coords = new float[6 * 4 * text.length()];
		int n = 0;
		for (const char* p = text.c_str(); *p; p++) {
			float x2 = x +characters->at(*p)->bl * sx;
			float y2 = -y -characters->at(*p)->bt * sy;
			float w =characters->at(*p)->bw * sx;
			float h =characters->at(*p)->bh * sy;

			/* Advance the cursor to the start of the next character */
			x +=characters->at(*p)->ax * sx;
			y +=characters->at(*p)->ay * sy;

			/* Skip glyphs that have no pixels */
			if (!w || !h)
				continue;

			float* arr1 = new float[] { x2, -y2,characters->at(*p)->tx, 0};
			float* arr2 = new float[] { x2 + w, -y2,characters->at(*p)->tx +characters->at(*p)->bw / atlasWidth, 0 };
			float* arr3 = new float[] { x2, -y2 - h,characters->at(*p)->tx,characters->at(*p)->bh / atlasHeight };
			float* arr4 = new float[] { x2 + w, -y2,characters->at(*p)->tx +characters->at(*p)->bw / atlasWidth, 0};
			float* arr5 = new float[] { x2, -y2 - h,characters->at(*p)->tx,characters->at(*p)->bh / atlasHeight };
			float* arr6 = new float[] { x2 + w, -y2 - h,characters->at(*p)->tx +characters->at(*p)->bw / atlasWidth,characters->at(*p)->bh / atlasHeight };

			CopyToArray(coords, arr1, n + 0, 4);
			CopyToArray(coords, arr2, n + 4, 4);
			CopyToArray(coords, arr3, n + 8, 4);
			CopyToArray(coords, arr4, n + 12, 4);
			CopyToArray(coords, arr5, n + 16, 4);
			CopyToArray(coords, arr6, n + 20, 4);

			n += 24;
		}

		printf("\n %d =============================\n", (6 * 4 * text.length()));
		for (int i = 0; i < 6 * 4 * text.length(); i+=4) {
			printf("\n%f %f %f %f", coords[i], coords[i + 1], coords[i + 2], coords[i + 3]);
		}
		printf("\n=============================\n");

		auto shaderId = ResourceManager::CreateShader("Assets/Shaders/Fonts/FontShader.shader");
		auto shader = ResourceManager::GetShader(shaderId);

		VertexArray* vArray = VertexArray::Create();
		VertexBuffer* vBuffer = VertexBuffer::CreateBuffer(coords, 6 * 4 * text.length());
		Material* texMat = new Material(shader, nullptr, 0);
		BufferLayout layout = {
			{ShaderDataType::Float2, "a_Position", false},
			{ShaderDataType::Float2, "tex_coords", false}
		};

		vBuffer->SetLayout(layout);
		vArray->AddVertexBuffer(vBuffer);

		return new RenderRequest("TEXT_RENDER_" + text, vArray, texMat, RendererAPI::RenderPrimitive::TRIANGLES, 0, false, false, true);

	}
}