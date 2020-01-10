#include "Aimbot.h"
#include "Verlet.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>
#include "Log.h"
#include <math.h>

#define PI 3.14159265


bool Collided(Vec3d* ball_pos, Vec3d* target_pos)
{
	if (ball_pos == target_pos)
		return true;
}

Vec3d* Aimbot(Cannon cannon, Enemy koopa, Ball ball, float dt,Vec3d windForce)
{
	Vec3d* ret = (0,0,0);
	
	particle ballPos;
	ballPos.pos.x = cannon.x;
	ballPos.pos.y = cannon.y;
	ballPos.acc.y = 980.0f;
	ballPos.speed.x = 0.0f;
	ballPos.speed.y = 0.0f;
	ballPos.mass = 0.5f;

	int koopaCenter_x = koopa.x + koopa.koopaRect.w / 2;
	int koopaCenter_y = koopa.y + koopa.koopaRect.h / 2;

	int ballCenter_x = cannon.x + ball.rect.w /2;
	int ballCenter_y = cannon.y + ball.rect.h /2;

	//MonteCarlo
	int i = 0;
	int k = 0;
	while(i<500) // Try at most 
	{
		ballPos.pos.x = cannon.x;
		ballPos.pos.y = cannon.y;

		ballPos.speed.x = rand() % 750 + 0;
		ballPos.speed.y = -(rand() % 1500 + 0);

		Vec3d randSpeed = ballPos.speed;

		for (int j = 0; j < 1000; j++)
		{
			
			Verlet(&ballPos, &ballPos, windForce, dt);
			
			//Update Koopa center
			koopaCenter_x = koopa.x + koopa.koopaRect.w / 2;
			koopaCenter_y = koopa.y + koopa.koopaRect.h / 2;

			ballCenter_x = ballPos.pos.x + ball.rect.w / 2;
			ballCenter_y = ballPos.pos.y + ball.rect.h / 2;

			int dx = ballCenter_x - koopaCenter_x;
			int dy = ballCenter_y - koopaCenter_y;

			if( sqrt((dx*dx)+(dy*dy)) <= 50)
			{
				LOG("Hit!");
				ret = &randSpeed;
				return ret;
			}
			k = 0;
		}
		i++;
	}
	return &Vec3d();
}