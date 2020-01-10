#include "Verlet.h"
#include "Log.h"

void Verlet(particle* prev_part, particle* output_part, Vec3d force, float dt)
{
	//Wind force
	output_part->acc.x = force.x * 5;
	output_part->acc.y = prev_part->acc.y;
	output_part->acc.z = prev_part->acc.z;

	//Calculate new speed based on prev speed and acceleration
	output_part->speed.x = prev_part->speed.x + output_part->acc.x * dt; // v = vi + a*t
	output_part->speed.y = prev_part->speed.y + output_part->acc.y * dt;
	output_part->speed.z = prev_part->speed.z + output_part->acc.z * dt;

	//Calculate position based on previous position and new speed and acceleration
	output_part->pos.x = prev_part->pos.x + output_part->speed.x * dt + 0.5f * output_part->acc.x * dt * dt; // x = xi + v*t + 1/2*a*t*t
	output_part->pos.y = prev_part->pos.y + output_part->speed.y * dt + 0.5f * output_part->acc.y * dt * dt;
	output_part->pos.z = prev_part->pos.z + output_part->speed.z * dt + 0.5f * output_part->acc.z * dt * dt;
	//LOG("speed : %f ", prev_part->speed.y);

}