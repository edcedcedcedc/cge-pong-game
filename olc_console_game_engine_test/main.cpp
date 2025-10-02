#include "..\..\olc_cge\olcConsoleGameEngine.h"
#include <string>


struct Paddle {
    float x;
    int y;
    float width;
    int height;
    float speed;
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
    PongGame() { m_sAppName = L"PongGame"; }

protected:
    Game game;

    virtual bool OnUserCreate()
    {
        game.gameOver = false;
        game.score = 0;

        game.ball.size = 1;
        game.ball.x = ScreenWidth() / 2;
        game.ball.y = ScreenHeight() / 2;
        game.ball.dx = 20.0f;
        game.ball.dy = 20.0f;

        game.paddle.width = 15;
        game.paddle.height = 1;
        game.paddle.x = (ScreenWidth() / 2) - (game.paddle.width / 2);
        game.paddle.y = ScreenHeight() - game.paddle.height;
        game.paddle.speed = 0.2;

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
      
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

        if (!game.gameOver)
        {   
            FillCircle((int)game.ball.x, (int)game.ball.y, game.ball.size, PIXEL_HALF, FG_WHITE);
            DrawLine(game.paddle.x, game.paddle.y,game.paddle.x + game.paddle.width, 
                game.paddle.y,PIXEL_SOLID, FG_YELLOW);
            
            std::wstring textScore = L"Score: " + std::to_wstring(game.score);
            DrawString(0,0, textScore, FG_WHITE);

            if (GetKey(VK_LEFT).bHeld)  game.paddle.x -= game.paddle.speed;
            if (GetKey(VK_RIGHT).bHeld)  game.paddle.x += game.paddle.speed;

            if (game.paddle.x < 0) game.paddle.x = 0;
            if (game.paddle.x + game.paddle.width > ScreenWidth()) 
                game.paddle.x = ScreenWidth() - game.paddle.width;


#if 0
            std::wstring debugText =
                L"Ball X: " + std::to_wstring((int)game.ball.x) +
                L" Y: " + std::to_wstring((int)game.ball.y) +
                L" Ball bottom: " + std::to_wstring((int)(game.ball.y + game.ball.size)) +
                L"\nPaddle X: " + std::to_wstring((int)game.paddle.x) +
                L" Y: " + std::to_wstring((int)game.paddle.y) +
                L" Paddle right: " + std::to_wstring((int)(game.paddle.x + game.paddle.width));
            DrawString(0, 0, debugText, FG_WHITE);
#endif
            
            game.ball.x += game.ball.dx * fElapsedTime;
            game.ball.y += game.ball.dy * fElapsedTime;


            float paddleLeft = game.paddle.x;
            float paddleRight = game.paddle.x + game.paddle.width;
            float paddleCenter = game.paddle.x + game.paddle.width / 2;
             
            if (game.ball.y + game.ball.size > game.paddle.y + game.paddle.height)
                game.gameOver = true;

          
            

            if (game.ball.y + game.ball.size >= game.paddle.y && // bottom of ball >= top of paddle
                game.ball.y + game.ball.size <= game.paddle.y + game.paddle.height && // prevent multiple bounces
                game.ball.x >= paddleLeft &&
                game.ball.x <= paddleRight)
            {
                game.ball.dy *= -1;
                game.ball.y = game.paddle.y - game.ball.size;
                game.score += 1;

                float hitPos = (game.ball.x - paddleCenter) / (game.paddle.width / 2);
                game.ball.dx = 20.0f * hitPos;

                if (game.score % 3 == 0) {
                    if (game.ball.dy > 0) game.ball.dy += 1.0f; else game.ball.dy -= 1.0f;
                }
            }

            if (game.ball.y + game.ball.size <= 0)
            {
                game.ball.dy *= -1;
                game.ball.y = game.ball.size;
            }

            if (game.ball.x <= 0)
            {
                game.ball.dx *= -1;
                game.ball.x = 0;
            }

            if (game.ball.x + game.ball.size >= ScreenWidth())
            {
                game.ball.dx *= -1;
                game.ball.x = ScreenWidth() - game.ball.size;
            }

            
        }
        else
        {   
            std::wstring textEndGame = L"GAME OVER";
            DrawString(ScreenWidth() / 2 - textEndGame.size()/2, ScreenHeight() / 2, textEndGame, FG_WHITE);
        }

        return true;
    }
};

int main()
{
    PongGame demo;
    demo.ConstructConsole(120, 30, 8, 8);
    demo.Start();
    return 0;
}
