#include "ingame.h"
#include <SDL.h>
#include <iostream>
#include <SDL_test_font.h>
#include <string>
#include <vector>

 void setupGraphic(GraphicContext& context)
{
	// error message
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized: " <<
			SDL_GetError();
		exit(1);
	}
	else
	{
		std::cout << "SDL video system is ready to go\n";
	}
	context.window = nullptr;
	context.texture = nullptr;
	context.render = nullptr;

	if (SDL_GetDisplayBounds(0, &context.display) != 0)
	{
		std::cout << "SDL_GetDisplayBounds failed: " << SDL_GetError();
		SDL_Quit();
		exit(1);
	}
	context.windowW = context.display.w; //get size display for screen
	context.windowH = context.display.h;

	context.window = SDL_CreateWindow("Chrome dinosaurs",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		context.windowW,
		context.windowH,
		SDL_WINDOW_FULLSCREEN);

	if (context.window == NULL)
	{
		std::cout << "Can not creat window\n";
		exit(1);
	}

	context.render = SDL_CreateRenderer(context.window, -1, SDL_RENDERER_ACCELERATED);

	if (context.render == NULL)
	{
		std::cout << "Can not create renderer\n";
		SDL_DestroyWindow(context.window);
		SDL_Quit();
		exit(1);
	}
	// Set up game
	context.game_over = false;
	context.set_up_game_over = false;
	context.player = X; // player X starts first
	context.player1.curImage = "player1_on.bmp";
	context.player2.curImage = "player2_off.bmp";
	context.timer_button.dis_time = COUNTDOWN / 1000; //ticks -> seconds
	context.timer_button.curImage = "timer/timer_60.bmp"; // timer at 01:00

}

 void destroyGraphic(GraphicContext& context)
{
	if (context.texture != nullptr)
	{
		SDL_DestroyTexture(context.texture);
		context.texture = nullptr;
	}
	if (context.render != nullptr)
	{
		SDL_DestroyRenderer(context.render);
		context.render = nullptr;
	}
	if (context.window != nullptr)
	{
		SDL_DestroyWindow(context.window);
		context.window = nullptr;
	}
	SDL_Quit();
}

 void game_over(GraphicContext& context, int w, int h)
{
	int x = w / 2; // x pos
	int y = h / 2; // y pos

	(context.player == X) ? (context.winner.curImage = "player2_win.bmp") :
		(context.winner.curImage = "player1_win.bmp");

	std::string path = "RESOURCE/" + context.winner.curImage; // get path image
	SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str()); // get size of image
	if (tempSurface == nullptr)
	{
		std::cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	int imgW = (tempSurface->w) * h / (tempSurface->h);
	int imgH = h;
	SDL_FreeSurface(tempSurface);
	context.winner.rect =
	{
		x - imgW / 2,
		y - imgH / 2,
		imgW,
		imgH
	};


}

 bool checkMouseInButton(const SDL_Rect& button, int x, int y)
{
	if (x >= button.x && x <= (button.x + button.w) &&
		y >= button.y && y <= (button.y + button.h))
	{
		return true;
	}
	return false;
}

 void drawImage(GraphicContext& context, const SDL_Rect& button, std::string text)
{
	text = "RESOURCE/" + text; // get path image
	SDL_Surface* tempSurface = SDL_LoadBMP(text.c_str());
	if (tempSurface == nullptr)
	{
		std::cout << "Unable to load image " << text << " SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(context.render, tempSurface);
	SDL_FreeSurface(tempSurface);
	if (tempTexture == nullptr)
	{
		std::cout << "Unable to create texture from " << text << " SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderCopy(context.render, tempTexture, NULL, &button); // draw image

	SDL_DestroyTexture(tempTexture);
}

 void timerFunction(GraphicContext& context)
{
	if (context.timer_button.isRunning)
	{
		context.timer_button.current_time = SDL_GetTicks();
		context.timer_button.time_left =
			COUNTDOWN - (context.timer_button.current_time - context.timer_button.start_time);
		if (context.timer_button.time_left <= 0) // time out
		{
			context.timer_button.isRunning = false;
			context.game_over = true;
			context.timer_button.dis_time = 0;
			return;
		}
		else
		{
			if (context.timer_button.time_left / 1000 != context.timer_button.dis_time)
			{
				//if (context.timer_button.dis_time * 1000 != context.timer_button.time_left)
				context.timer_button.dis_time = context.timer_button.time_left / 1000;
				context.timer_button.curImage = "timer/timer_" + std::to_string(context.timer_button.dis_time) + ".bmp";

			}

		}
	}
}

 void resetBoard(GraphicContext& context)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			context.board[i][j] = EMPTY;
		}
	}
	context.player = X;
	context.game_over = false;
}

 void drawTable(GraphicContext& context, int w, int h)
{

	int cellW = w / 16;
	int cellH = cellW;

	SDL_SetRenderDrawColor(context.render, 0, 0, 0, 255);
	for (int i = 5; i <= 11; i += 2)
		SDL_RenderDrawLine(context.render, i * cellW, cellH, i * cellW, 7 * cellH);// column 

	for (int i = 1; i <= 7; i += 2)
		SDL_RenderDrawLine(context.render, 5 * cellW, i * cellH, 11 * cellH, i * cellH); // row



	context.player1.rect =
	{
		cellW  ,
		cellH * 5 / 2,
		cellW * 3,
		cellH
	};

	context.player2.rect =
	{
		cellW ,
		cellH * 9 / 2,
		cellW * 3,
		cellH
	};

	context.timer_button.rect =
	{
		cellW * 12,
		cellH ,
		cellH * 3,
		cellH * 3 / 2,
	};
}

 void drawSymbol(GraphicContext& context, int w, int h)
{
	if (context.game_over) return;
	int cellW = w / 16;
	int cellH = cellW;

	SDL_SetRenderDrawColor(context.render, 255, 0, 0, 255);
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (context.board[r][c] != EMPTY)
			{
				int x = (c * 2 + 6) * cellW;
				int y = (r * 2 + 2) * cellH; // get pos to draw symbol 
				const char* symbol = (context.board[r][c] == X) ? "X" : "O";
				(symbol == "X") ? SDL_SetRenderDrawColor(context.render, 255, 0, 0, 255) :
					SDL_SetRenderDrawColor(context.render, 0, 0, 255, 255);
				SDLTest_DrawString(context.render, x, y, symbol);
			}

		}
	}
}

 void handleMouseClick(GraphicContext& context, int mouseX, int mouseY, int w, int h)
{
	if (context.game_over) return;
	int cellW = w / 16;
	int cellH = cellW;
	int col = (mouseX / cellW) / 2 + (mouseX / cellW) % 2 - 3;
	int row = (mouseY / cellH) / 2 + (mouseY / cellH) % 2 - 1; // from mouse pos to row, col of board
	if (col >= 0 && row >= 0 && col < 3 && row < 3)
	{
		if (context.board[row][col] == EMPTY)
		{
			context.timer_button.isRunning = true;
			context.board[row][col] = context.player;
			if (context.player == X)
			{
				context.player1.curImage = "player1_off.bmp";
				context.player2.curImage = "player2_on.bmp";
				context.player = O;
			}
			else
			{
				context.player1.curImage = "player1_on.bmp";
				context.player2.curImage = "player2_off.bmp";
				context.player = X;
			}
			context.timer_button.start_time = SDL_GetTicks(); // reset timer

		}
	}
}

 void inGame(GraphicContext& context)
{
	while (SDL_PollEvent(&context.event))
	{
		if (context.event.type == SDL_QUIT)
		{
			context.game_is_running = false;
		}
		if (context.event.type == SDL_KEYDOWN)
		{
			if (context.event.key.keysym.sym == SDLK_ESCAPE)
			{
				context.game_is_running = false;
			}
		}
		if (context.event.type == SDL_MOUSEBUTTONDOWN)
		{
			int mouseX = context.event.button.x;
			int mouseY = context.event.button.y;
			handleMouseClick(context, mouseX, mouseY, context.windowW, context.windowH);
		}
	}
	SDL_SetRenderDrawColor(context.render, 255, 255, 255, 255);
	SDL_RenderClear(context.render);
	drawTable(context, context.windowW, context.windowH);
	drawSymbol(context, context.windowW, context.windowH); // draw X, O
	drawImage(context, context.player1.rect, context.player1.curImage); // draw player1
	drawImage(context, context.player2.rect, context.player2.curImage); // draw player2
	drawImage(context, context.timer_button.rect, context.timer_button.curImage); // draw timer
	timerFunction(context); // update timer
	if (context.game_over) // game over
	{
		if (!context.set_up_game_over)
		{
			game_over(context, context.windowW, context.windowH);
			context.set_up_game_over = true;
		}
		drawImage(context, context.winner.rect, context.winner.curImage);
	}
	SDL_RenderPresent(context.render);
}

 void gameRunning(GraphicContext& context)
{
	context.game_is_running = true;
	while (context.game_is_running)
	{
		inGame(context);
	}
}
