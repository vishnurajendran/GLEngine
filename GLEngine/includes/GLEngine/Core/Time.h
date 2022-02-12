#pragma once
#include "Core.h"

namespace GLengine {
	class GLENGINE_API Time {
		static float lastFrameTime;
	public:
		static float deltaTime;
		static float time;
		static void Update();
	};
}