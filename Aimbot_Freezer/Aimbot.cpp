#include "Aimbot.h"
#include "Verlet.h"
#include "SDL/include/SDL.h"

bool collided(Vec3d* ball_pos, Vec3d* target_pos)
{
	if (ball_pos == target_pos)
		return true;
}

void aimbot(Vec3d* shooter_pos, Vec3d* target_pos, float dt)
{
	Canon canon;
	Vec3d force;
	force.x = -10.0f;
	force.y = 980.0f;
	force.z = 0;
	particle ballPos;
	ballPos.pos.x = shooter_pos->x;
	ballPos.pos.y = shooter_pos->y;
	ballPos.acc.y = 0.0f;
	ballPos.speed.x = 0.0f;
	ballPos.speed.y = 0.0f;
	ballPos.mass = 0.5f;
	while (!collided(&ballPos.pos,target_pos))
	{
		
		
		Verlet(&ballPos, &ballPos, force, dt);
	}
}