#include "Aimbot.h"
#include "Verlet.h"
#include "SDL/include/SDL.h"

bool collided(Vec3d* ball_pos, Vec3d* target_pos)
{
	if (ball_pos == target_pos)
		return true;
}

void aimbot(Vec3d* shooter_pos, Vec3d* target_pos)
{
	Canon canon;
	Vec3d force;
	force.x = -10.0f;
	force.y = 980.0f;
	force.z = 0;
	particle ballP;
	ballP.pos.x = shooter_pos->x;
	ballP.pos.y = shooter_pos->y;
	ballP.acc.y = 0.0f;
	ballP.speed.x = 0.0f;
	ballP.speed.y = 0.0f;
	ballP.mass = 0.5f;
	while (!collided(shooter_pos,target_pos))
	{
		//Verlet(&shooter_pos,&shooter_pos,force,)
	}
}