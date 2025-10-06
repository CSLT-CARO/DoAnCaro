#ifndef INGAME_H
#define INGAME_H
#include <SDL.h>
#include <iostream>
#include <SDL_test_font.h>
#include <string>
#include <vector>

const int COUNTDOWN = 60000;
enum Cellstage
{
	EMPTY = 0,
	X,
	O,

};

enum Stage
{
	InGame,
	Pause,
	GameOver

};

struct Button
{
	SDL_Rect rect;
	std::string curImage;
};

struct Timer
{
	SDL_Rect rect;
	std::string curImage;
	int start_time;
	int time_left;
	int dis_time;
	int current_time;
	bool isRunning;
};

struct GraphicContext
{
	// size screen
	int windowH;
	int windowW;
	// SDL Graphic
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* texture;
	SDL_Surface* image;
	// Material
	SDL_Rect display;
	SDL_Event event;
	Cellstage board[3][3];
	Cellstage player;
	// Button
	Button player1;
	Button player2;
	Button winner;
	Timer timer_button;


	// Game status
	bool game_is_running;
	bool game_over;
	bool set_up_game_over;
};

struct GameOverButton
{
	std::vector <std::string> name_button = { "Restart", "Newgame", "Exit" };
	std::vector <std::string> name_button_on = { "Restart_on", "Newgame_on", "Exit_on" };
	enum eButton
	{
		Restart,
		Newgame,
		Exit
	};
};

 void setupGraphic(GraphicContext& context);

 void destroyGraphic(GraphicContext& context);

 void game_over(GraphicContext& context, int w, int h);

 bool checkMouseInButton(const SDL_Rect& button, int x, int y);

 void drawImage(GraphicContext& context, const SDL_Rect& button, std::string text);

 void timerFunction(GraphicContext& context);

 void resetBoard(GraphicContext& context);

 void drawTable(GraphicContext& context, int w, int h);

 void drawSymbol(GraphicContext& context, int w, int h);

 void handleMouseClick(GraphicContext& context, int mouseX, int mouseY, int w, int h);

 void inGame(GraphicContext& context);

 void gameRunning(GraphicContext& context);



#endif
