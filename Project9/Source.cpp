#include <stdio.h>
#include <raylib.h>
#include <iostream>
#define RAYGUI_IMPLEMENTATION 
#include <raygui.h>
#include <time.h>
#include <raymath.h>
#include <stdlib.h>
#include <buttonstyle.h>
#define UNNAMED_STYLE_PROPS_COUNT  6
int player1score;
int player2score;
int cpuscore;
int countsound;
Color p1 = Color{ 253,138,138,255};
Color p2 = Color{241,247,181,255};
Color b1 = Color{253,132,31,255};
class BALL
{
public:
	float x, y;
	int radius;
	int x_speed, y_speed;
	void Draw()
	{
		DrawCircle(x,y, radius, b1);
	}
	void update()
	{
		if (x - radius <= 0 && 265 <= y && y <= 534)
		{
			player1score++;
			y = GetScreenHeight() / 2;
			x = GetScreenWidth() / 2 - 140;
			x_speed = 0;
			y_speed = 0;
			countsound++;
		}
		if ((y + radius >= GetScreenHeight() || y - radius <= 0) && (y <= 265 || y >= 534))
		{
			y_speed *= -1;
		}
		if (x+radius >= GetScreenWidth() && y>=265 && y<=534)
		{
			y = GetScreenHeight() / 2;
			x = GetScreenWidth() / 2 + 117;
			x_speed = 0;
			y_speed = 0;
			cpuscore++;
			player2score++;
			countsound++;
		}
		if (x + radius >= GetScreenWidth() || x - radius <= 0)
		{
			x_speed *= -1;
		}
		
		x += x_speed;
		y += y_speed;
	}
};
class paddle
{
public:
	float x, y;
	int radius = 70;
	int x_speed=0, y_speed=0;
	void Draw()
	{
		DrawCircle(x, y, radius, p1);
	}
	void update()
	{

	if (y + radius >= GetScreenHeight() && IsKeyDown(KEY_S))
		{
			y_speed += 0;
		}
	else if (y - radius <= 0 && IsKeyDown(KEY_W))
	{
		y_speed +=0;
	}
	else if (x + radius >= GetScreenWidth()/2 && IsKeyDown(KEY_D))
		{
			x_speed +=0;
		}
	else if (x - radius <= 0 && IsKeyDown(KEY_A))
	{
		x_speed += 0;
	}
	else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))
	{
		y += y_speed - 5;
		x += x_speed;
	}
	else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))
	{
		y += y_speed - 5;
		x -= x_speed;
	}
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D))
	{
		y -= y_speed - 5;
		x += x_speed;
	}
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A))
	{
		y -= y_speed - 5;
		x -= x_speed;
	}
	else if (IsKeyDown(KEY_S))
		{
			y += y_speed;
		}
	else if (IsKeyDown(KEY_W))
		{
			y -= y_speed;
		}
	else if (IsKeyDown(KEY_D))
		{
			x += x_speed;
		}
	else if (IsKeyDown(KEY_A))
		{
			x -= x_speed;
		}

	}

};

class player2paddle
{
public:
	float x, y;
	int radius;
	int x_speed = 0, y_speed = 0;
	void Draw()
	{
		DrawCircle(x, y, radius, p2);
	}
	void update()
	{

		if (y + radius >= GetScreenHeight() && IsKeyDown(KEY_DOWN))
		{
			y_speed += 0;
		}
		else if (y - radius <= 0 && IsKeyDown(KEY_UP))
		{
			y_speed += 0;
		}
		else if (x + radius >= GetScreenWidth() && IsKeyDown(KEY_RIGHT))
		{
			x_speed += 0;
		}
		else if (x - radius <= GetScreenWidth()/2 && IsKeyDown(KEY_LEFT))
		{
			x_speed += 0;
		}
		else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT))
		{
			y += y_speed-5;
			x += x_speed;
		}
		else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT))
		{
			y += y_speed-5;
			x -= x_speed;
		}
		else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT))
		{
			y -= y_speed-5;
			x += x_speed;
		}
		else if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT))
		{
			y -= y_speed-5;
			x -= x_speed;
		}
		else if (IsKeyDown(KEY_DOWN))
		{	
			y += y_speed;
		}
		else if (IsKeyDown(KEY_UP))
		{
			y -= y_speed;
		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			x += x_speed;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			x -= x_speed;
		}

	}
};
BALL ball;
class cpupaddle
{
public:
float x=1500, y = 400, radius=70;
int speed_x, speed_y;
void Draw()
{
	DrawCircle(x, y, radius, p2);
}
void update()
{
	if (ball.x < x && ball.x >= 900)
	{
		x -= 7;
	}
	if (ball.y < y && y >= 0 && y>=0 && ball.x >= 800)
	{
		y -= 7;
	}
	if (ball.y > y && y <= GetScreenHeight() && ball.x >= 800)
	{
		y += 7;
	}
	if (ball.x > x && ball.x >= 800)
	{
		x += 7;
	}

}

};
cpupaddle cpu;
paddle player;
player2paddle player2;
int main()
{
	Rectangle start = { 620,720,140,70 };
	Rectangle mplayer = {800,720,140,70 };
	Rectangle back = { 72,42,240,120 };
	Rectangle playagain = { 670,650,260,80 };
	Rectangle pause = { 52,47,80,80 };
	Rectangle cont = {705,300,160,80};
	Rectangle exit = {705,410,160,100};
	bool pausepressed = false;
	bool startpressed = false;
	bool mplayerpressed = false;
	bool menupressed = false;
	bool backpressed = false;
	bool playagainpressed = false;
	bool contpressed = false;
	bool exitpressed = false;
	int screenwidth = 1600;
	int screenheight = 800;
	int count = 0;
	int i = 0,j=0;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	ball.x = screenwidth / 2-14;
	ball.y = screenheight / 2;
	ball.x_speed = 0;
	ball.y_speed = 0;
	ball.radius = 30;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	player.x = 100;
	player.y = screenheight / 2;
	player.x_speed = 11;
	player.y_speed = 11;
	player.radius = 70;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	player2.x = 1500;
	player2.y = screenheight / 2;
	player2.x_speed = 11;
	player2.y_speed = 11;
	player2.radius = 70;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	InitWindow(screenwidth, screenheight, "HOCKEY");
	InitAudioDevice();
	Music win=LoadMusicStream("winsound1111.mp3");
	PlayMusicStream(win);
	Texture2D bg = LoadTexture("mainmenu.png");
	Texture2D cpubg = LoadTexture("cpubg.png");
	Texture2D score = LoadTexture("scorescreen.png");
	Texture2D mulbg = LoadTexture("multiplayer.png");
	Texture2D htp = LoadTexture("howtoplay.png");
	Texture2D pausescreen = LoadTexture("pausescreen.png");
	Music bgplay = LoadMusicStream("alltime.mp3");
	Music Collision = LoadMusicStream("collision sound.wav");
	PlayMusicStream(Collision);
	PlayMusicStream(bgplay);
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		
		UpdateMusicStream(bgplay);
		i = GetRandomValue(1, 2);
		j = GetRandomValue(1, 2);
		if (CheckCollisionCircles(Vector2{ ball.x,ball.y }, ball.radius, Vector2{ player.x,player.y }, player.radius))
		{
			UpdateMusicStream(Collision);
			if (ball.y > player.y)
			{
				ball.y_speed =11;
			}
			if (ball.y < player.y)
			{
				ball.y_speed = -11;
			}
			if (ball.x > player.x)
			{
				ball.x_speed = 11;
			}
			if (ball.x < player.x)
			{
				ball.x_speed = 11;
			}
			ball.x_speed *= i;
			ball.y_speed *= j;
		}
		if (CheckCollisionCircles(Vector2{ ball.x,ball.y }, ball.radius, Vector2{ cpu.x,cpu.y }, cpu.radius))
		{
			UpdateMusicStream(Collision);
			if (ball.y > player2.y)
			{
				ball.y_speed = 11;
			}
			if (ball.y < player2.y)
			{
				ball.y_speed = -11;
			}
			if (ball.x > player2.x)
			{
				ball.x_speed = 11;
			}
			if (ball.x < player2.x)
			{
				ball.x_speed = -11;
			}
			ball.x_speed *= i;
			ball.y_speed = j;
		}
		if (countsound == 1)
		{
			
			countsound = 0;
		}
		if (count == 0)
		{
			startpressed = GuiButton(start, "START GAME");
			mplayerpressed = GuiButton(mplayer, "HOW TO PLAY");
			DrawTexture(bg, 0, 0, WHITE);
			
		}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		if (mplayerpressed)
		{
			count = 2;
			mplayerpressed = false;
		}
		if (playagainpressed)
		{
			player1score = 0;
			player2score = 0;
			count = 1;
			playagainpressed = false;
			ball.x = screenwidth / 2 - 14;
			ball.y = screenheight/2;
			player.x = 100;
			player.y = screenheight / 2;
			player2.x = 1500;
			player2.y = screenheight / 2;
		}
		if (startpressed)
		{
			count = 1;
			startpressed=false;
			
		}
		if (cpuscore == 3 || player2score == 3)
		{
			count = 3;

		}
		if (backpressed)
		{
			count = 0;
			backpressed = false;
		}
		if (pausepressed)
		{
			count = 4;
			pausepressed = false;
		}
		if (contpressed)
		{
			count = 1;
			ResumeMusicStream(bgplay);
			contpressed = false;
		}
		if (exitpressed)
		{
			count = 0;
			exitpressed = false;
		}
		if (count == 4)
		{
			exitpressed = GuiButton(exit, "EXIT");
			contpressed = GuiButton(cont, "CONTINUE");
			DrawTexture(pausescreen, 0, 0, WHITE);
			DrawText("GAME    PAUSED",600,200,50, WHITE);
			PauseMusicStream(bgplay);
		}
		if (count == 3)
		{
			UpdateMusicStream(win);
			playagainpressed = GuiButton(playagain, "    ");
			DrawTexture(score, 0, 0, WHITE);
			DrawText("GAME    ENDED", 600, 200, 50, WHITE);
			DrawText(TextFormat("%i", cpuscore), 715, 370, 100, WHITE);
			DrawText(TextFormat("%i", player1score), 835, 370, 100, WHITE);
			if (player1score > player2score)
			{
				DrawText("CPU     WINS", 595, 600, 50, WHITE);
			}
			if (player2score > player1score)
			{
				DrawText("PLAYER   1 WINS", 565, 600, 50, WHITE);
			}
		}
		
		else if (count == 1)
		{
			
			ball.update();
			player.update();
			cpu.update();
			ClearBackground(BLACK);
			pausepressed = GuiButton(pause, "   ");
			DrawTexture(cpubg, 0, 0, WHITE);
			DrawText(TextFormat("%i", cpuscore), 400, 100, 100, WHITE);
			DrawText(TextFormat("%i", player1score), 1200, 100, 100, WHITE);
			ball.Draw();
			cpu.Draw();
			player.Draw();
		}
		else if (count == 2)
		{
			backpressed = GuiButton(back, "    ");
			ClearBackground(WHITE);
			DrawTexture(htp,0,0,WHITE);
			
		}
		EndDrawing();
	}
	CloseWindow();
	CloseAudioDevice();
	UnloadMusicStream(win);
	UnloadMusicStream(bgplay);
	UnloadMusicStream(Collision);
}
