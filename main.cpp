#include "ingame.h"
#include <SDL.h>
#include <iostream>
#include <SDL_test_font.h>
#include <string>
#include <vector>



int main(int argc, char* argv[])
{
	GraphicContext graphic{};
	graphic.window = nullptr;
	graphic.render = nullptr;
	graphic.texture = nullptr;
	graphic.image = nullptr;

	setupGraphic(graphic);

	gameRunning(graphic);

	destroyGraphic(graphic);
	return 0;
}