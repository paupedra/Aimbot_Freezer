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

Vec3d* Aimbot(Cannon cannon, Enemy koopa, Ball ball, float dt)
{
	Vec3d* ret = (0,0,0);

	Vec3d force;
	force.x = -10.0f;
	force.y = 98.0f;
	force.z = 0;
	particle ballPos;
	ballPos.pos.x = cannon.x;
	ballPos.pos.y = cannon.y;
	ballPos.acc.y = 0.0f;
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
	while(i<50) // Try at most 
	{
		//collided = false;
		//Trajectory.clear();
		//double angle = rand() % 90;
		//double velocity = rand() % 500;
		//double velocity_x = sin(angle*(PI / 180)) * velocity;
		//double velocity_y = cos(angle*(PI / 180)) * velocity;

		ballPos.pos.x = cannon.x;
		ballPos.pos.y = cannon.y;



		//ballPos.speed.x = rand() % 300 + 100;
		//ballPos.speed.y = rand() % 300 + 100;

		/*ballPos.speed.x = 100;
		ballPos.speed.y = 100;*/

		for (int j = 0; j < 300; j++)
		{
			//Trajectory.add(ballPos.pos);
			
			Verlet(&ballPos, &ballPos, force, dt);
			
			//Update Koopa center
			koopaCenter_x = koopa.x + koopa.koopaRect.w / 2;
			koopaCenter_y = koopa.y + koopa.koopaRect.h / 2;

			ballCenter_x = ballPos.pos.x + ball.rect.w / 2;
			ballCenter_y = ballPos.pos.y + ball.rect.h / 2;

			int dx = ballCenter_x - koopaCenter_x;
			int dy = ballCenter_y - koopaCenter_y;
			if( sqrt((dx*dx)+(dy*dy)) <= 200)
			{

				ret = (ballPos.speed.x, ballPos.speed.y,0);
				return ret;
				LOG("Hit!");
			}
			k = 0;
		}
		i++;
	}
	return ret;
}