#pragma once
#include "GLEngine/Core/Core.h"
#include "GLEngine/Rendering.h"
#include "GLEngine/HelperDefinitions.h"
#include "GLEngine/Core/Transform.h"
#include "GLEngine/Core/Component.h"
#include "GLEngine/Core/GameObject.h"

namespace GLengine {
	class GLENGINE_API Sprite2D : public IComponent {
		float* vertices;
		int vertSize;
		unsigned int* indices;
		int indxSize;
		Shape2D* shape;
		void GenerateShapeAttribs();
		void SetTransformationMatrix();
	public:
		Sprite2D();
		Sprite2D(Material* material);
		Sprite2D(Texture2D* texture);

		//re-definition of abstract class IComponent
		void Start();
		void Update();
		void OnDestroy();

		/// <summary>
		/// Draw the sprite.
		/// </summary>
		void DrawSprite();
	};
}