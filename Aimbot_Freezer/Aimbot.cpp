#include "Aimbot.h"
#include "Verlet.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>

bool Collided(Vec3d* ball_pos, Vec3d* target_pos)
{
	if (ball_pos == target_pos)
		return true;
}

void Aimbot(Cannon cannon, Enemy koopa, Ball ball, float dt)
{

	Vec3d force;
	force.x = -10.0f;
	force.y = 980.0f;
	force.z = 0;
	particle ballPos;
	ballPos.pos.x = cannon.x;
	ballPos.pos.y = cannon.y;
	ballPos.acc.y = 0.0f;
	ballPos.speed.x = 0.0f;
	ballPos.speed.y = 0.0f;
	ballPos.mass = 0.5f;

	

	bool collided;


	//MonteCarlo
	int i = 0;

	while(i<50) // Try at most 
	{
		collided = false;
		Trajectory.clear();

		int angle = rand() % 90;
		
		for (int j = 0; i < 300; j++)
		{
			
			Trajectory.add(ballPos.pos);
			
			Verlet(&ballPos, &ballPos, force, dt);


			if ((ball.ballCollider.x + ball.ballCollider.w > koopa.koopaCollider.x) && (ball.ballCollider.x < koopa.koopaCollider.x + koopa.koopaCollider.w) &&
				(ball.ballCollider.y + ball.ballCollider.h > koopa.koopaCollider.y) && (ball.ballCollider.y < koopa.koopaCollider.y + koopa.koopaCollider.h))
			{

				collided = true;
				Trajectory.add(ballPos.pos);
				return;

			}
			
		}
		i++;
	}
}