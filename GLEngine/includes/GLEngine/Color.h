#pragma once
#include<GLEngine/Core/Core.h>
#include<glm/glm.hpp>

namespace GLengine {
	class GLENGINE_API Color {
	public:
		float r=0, g=0, b=0, a=0;
		
		Color(glm::vec4 colVec) {
			this->r = colVec.r;
			this->g = colVec.g;
			this->b = colVec.b;
			this->a = colVec.a;
		}

		Color(float r, float g, float b, float a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		Color* Lerp(Color* a, Color* b, float t) {
			return new Color(glm::mix(a->GetVec4(), b->GetVec4(), t));
		}

		glm::vec4 GetVec4() {
			return glm::vec4(r, g, b, a);
		}

		static Color* Red() {
			return new Color(1, 0, 0, 1);
		}

		static Color* Blue() {
			return new Color(0, 0, 1, 1);
		}

		static Color* Green() {
			return new Color(0, 1, 0, 1);
		}

		static Color* Yellow() {
			return new Color(0, 1, 1, 1);
		}

		static Color* White() {
			return new Color(1, 1, 1, 1);
		}

		static Color* Black() {
			return new Color(0, 0, 0, 1);
		}
	};
}