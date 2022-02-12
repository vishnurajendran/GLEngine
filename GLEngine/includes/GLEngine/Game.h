#pragma once

#include "GLEngine/Core/Core.h"
#include <string>

namespace GLengine {

	class GLENGINE_API Game
	{
	public:
		virtual void Start();
		virtual void Loop();
		virtual void Exit();
	};

	//Defined in client

	Game* CreateGame();
	std::string GetGameName();
}