#ifdef GLENGINE_PLATFORM_WINDOWS

extern GLengine::Game* GLengine::CreateGame();
extern std::string GLengine::GetGameName();

int main(int argc, char** argv) {

	GLengine::Preferences::Initialise();
	GLengine::Engine engine;

	bool fullScreen = GLengine::Preferences::GetInt("Fullscreen") == 1;
	int width = GLengine::Preferences::GetInt("Width");
	int height = GLengine::Preferences::GetInt("Height");
	int fps = GLengine::Preferences::GetInt("Framerate");
	engine.Initialise(GLengine::GetGameName(), fullScreen, height, width, fps);
	auto game = GLengine::CreateGame();
	game->Start();

	//game loop
	while (engine.IsRunning())
	{
		engine.Run();
		game->Loop();
	}

	game->Exit();
	delete game;
	engine.Quit();

	return 0;
}

#endif