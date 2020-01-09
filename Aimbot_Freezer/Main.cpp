
#pragma comment(linker,"/ENTRY:mainCRTStartup")
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")

#include <stdlib.h>
#include <stdio.h>
#include "sdl_functions.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "Log.h"
#include "Verlet.h"
#include "Aimbot.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "SDL_ttf\include\SDL_ttf.h"


int main(int argc, char* argv[])
{
	// Initialize SDL
	if (Init() == 0) {
		return 1;
	}

	//FPS variables
	j1PerfTimer		ptimer;
	j1PerfTimer		delay_timer;
	int				frame_count = 0;
	j1Timer			startup_time;
	j1Timer			frame_time;
	j1Timer			last_sec_frame_time;
	int				last_sec_frame_count = 0;
	int				prev_last_sec_frame_count = 0;
	int				frame_rate = 60;
	float			dt = 0;
	SDL_Color textColor = { (255),(255),(255) };
	int angle = 45;


	//Load Font
	_TTF_Font* font = TTF_OpenFont("Assets/Fonts/Minecraftia-Regular.ttf", 20);

	// Load a texture
	SDL_Texture *texScreen = LoadTexture("Assets/Screens/Background.jpg");
	SDL_Texture *texBall = LoadTexture("Assets/Sprites/kirby_ball.png");
	SDL_Texture *textTexture = Print("45",textColor,font);
	SDL_Texture* texCanon = LoadTexture("Assets/Sprites/Canon.png");
	SDL_Texture *textTexture = Print("hola",textColor,font);

	float rotAngle = 0;
	Canon canon = {
		{0,0,512,512},
		texCanon,
		10, 550,
		rotAngle
	};

	Ball ball = {
		{0, 0, 200, 200}, // SDL_Rect
		texBall,          // SDL_Texture
		270, 100,         // Initial position in the screen
		0, 0              // Initial velocity
	};

	//Ball particle
	particle ball_p;
	ball_p.pos.x = 450; //Starting Position
	ball_p.pos.y = 200;
	ball_p.acc.y = 0.0f; //Gravity
	ball_p.speed.x = 0.0f; //Arbitrary starting speed
	ball_p.speed.y = 100.0f;
	ball_p.mass = 0.5f;

	particle tmp;

	particle old_state;

	Vec3d force;

	while (exitApplication != 1)
	{
		//Frame calculation
		frame_count++;
		last_sec_frame_count++;
		dt = frame_time.ReadSec();
		frame_time.Start(); //Restart the single frame time

		PreUpdate(); // Updates events
		
		/* Draw the screen */
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 1680;
		rect.h = 1050;
		Blit(texScreen, 0, 0, &rect,0);

		// Apply forces
		force.x = 0;
		force.y = 980.0f;
		force.z = 0;

		const Uint8* keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_O])
		{
			ball_p.pos.x = 450; //Starting Position
			ball_p.pos.y = 200;
		}
	
		if (keys[SDL_SCANCODE_RIGHT])
		{
			force.x += 500.0f;
		}
		if (keys[SDL_SCANCODE_LEFT])
		{
			force.x -= 500.0f;
		}

		if (keys[SDL_SCANCODE_UP] == KEY_DOWN)
		{
			angle += 1;
		}
		if (keys[SDL_SCANCODE_DOWN] == 0)
		{
			angle -= 1;
		}

		//Verlet
		Verlet(&ball_p, &ball_p, force, dt);

		if (ball_p.pos.y > 700)
		{
			ball_p.speed.y = -ball_p.speed.y * 0.8; //Floor Bounce
			ball_p.pos.y = 700;

			ball_p.speed.x = ball_p.speed.x * 1; //Friction
			
			if(ball_p.speed.x < 1 || ball_p.speed.x > -1)
			{
				ball_p.speed.x = 0;
			}
		}
		if (ball_p.pos.x > 1000) //Wall bounce
		{
			ball_p.speed.x = -ball_p.speed.x * 0.8;
			ball_p.pos.x = 1000;
		}
		if (ball_p.pos.x < 0)
		{
			ball_p.speed.x = -ball_p.speed.x * 0.8;
			ball_p.pos.x = 0;
		}

		

		/* Draw the ball */
		Blit(ball.tex, ball_p.pos.x, ball_p.pos.y, &ball.rect,0);

		//Update Text
		char buffer[6];
		sprintf_s(buffer, "%d", angle);
		SDL_DestroyTexture(textTexture);
		textTexture = Print(buffer, textColor, font);

		// Draw canon
		Blit(canon.tex, canon.x, canon.y, &canon.rect, rotAngle);

		//Draw Text
		Blit(textTexture, 100, 100,NULL,0);

		PostUpdate(); // Presents the screen

		//Frame Calculation and Delay to achieve desired framerate
		if (last_sec_frame_time.Read() > 1000)
		{
			LOG("%d", last_sec_frame_count);
			last_sec_frame_time.Start();
			last_sec_frame_count = 0;
		}

		//SDL_Delay
		if (frame_rate != 0)
		{
			if (1000 / frame_rate > frame_time.Read())
			{
				SDL_Delay((1000 / frame_rate) - frame_time.Read());
			}
		}
	}



	// Unload textures
	UnloadTexture(texBall);
	UnloadTexture(texScreen);

	// Finalize SDL
	CleanUp();

	return 0;
}
