#ifdef BuildSourcesGame_H
#defind BuildSourcesGame_H

struct GameManager
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* image = nullptr;
	int screenH;
	int screenW;
};

void buildSourcesGame(GameManager& gameManager)
{
	// Khoi tao che do hien thi
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	gameManager.screenH = displayMode.h, gameManager.screenW = displayMode.w; //Lay chieu rong/dai cua man hinh
	//Khoi tao man hinh window
	gameManager.window = SDL_CreateWindow("CaroGame",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gameManager.screenW, gameManager.screenH, SDL_WINDOW_SHOWN);

	// Khoi tao renderer (moi truong sdl2 dung de ve)
	gameManager.renderer = SDL_CreateRenderer(gameManager.window, -1, 0);
}

#endif // BuildSourcesGame_H
