
#include "..\..\olc_cge\olcConsoleGameEngine.h"


struct Paddle {
	float x;
	int y;
	int width;
	int speed;
};

struct Ball {
	float x, y;
	float dx, dy;
	int size;
};

struct Game {
	Paddle paddle;
	Ball ball;
	int score;
	bool gameOver;
};


class PongGame : public olcConsoleGameEngine
{
public:
	PongGame()
	{
		m_sAppName = L"PongGame";
	}
protected:
	
	Game game;

	virtual bool OnUserCreate()
	{	
		game.gameOver = false;
		game.score = 0;

		game.ball.size = 1;
		game.ball.x = ScreenWidth() / 2;
		game.ball.y = ScreenHeight() / 2;
		game.ball.dx = 1.0f;
		game.ball.dy = 1.0f;

		game.paddle.width = 10;
		game.paddle.x = (ScreenWidth() / 2) - (game.paddle.width / 2);
		game.paddle.y = ScreenHeight() - 2;
		game.paddle.speed = 1;

		

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);
		
		return true;
	}
};

int main()
{
	PongGame demo;
	demo.ConstructConsole(80, 30, 16, 16);
	demo.Start();
    return 0;
}


