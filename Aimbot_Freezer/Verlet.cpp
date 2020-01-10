#include "Verlet.h"
#include "Log.h"



void Verlet(particle* prev_part, particle* output_part, Vec3d force, float dt)
{

	Vec3d drag_force;
	// Original function to calculate the aerodinamic force

	//drag_force.x = 0.5f * 1.225f * prev_part->speed.x * prev_part->speed.x * 3.14159265f / 2.0f * 0.47f * ((prev_part->speed.x < 0) ? 1 : -1) ;
	//drag_force.y = 0.5f * 1.225f * prev_part->speed.y * prev_part->speed.y * 3.14159265f / 2.0f * 0.47f * ((prev_part->speed.y < 0) ? 1 : -1) ;
	//drag_force.z = 0.5f * 1.225f * prev_part->speed.z * prev_part->speed.z * 3.14159265f / 2.0f * 0.47f * ((prev_part->speed.z < 0) ? 1 : -1) ;

	// Modified function so it fits with the higher values we are currently using

	/*drag_force.x = 0.0904386f * prev_part->speed.x * prev_part->speed.x * ((prev_part->speed.x < 0) ? 1 : -1);
	drag_force.y = 0.0904386f * prev_part->speed.y * prev_part->speed.y * ((prev_part->speed.x < 0) ? 1 : -1);
	drag_force.z = 0.0904386f * prev_part->speed.z * prev_part->speed.z * ((prev_part->speed.x < 0) ? 1 : -1);
*/
	//Vec3d new_acc;
	//new_acc.x = (force.x + drag_force.x) / prev_part->mass;
	//new_acc.y = (force.y + drag_force.y) / prev_part->mass;
	//new_acc.z = (force.z + drag_force.z) / prev_part->mass;

	output_part->acc.x = prev_part->acc.x;
	output_part->acc.y = prev_part->acc.y;
	output_part->acc.z = prev_part->acc.z;

	//output_part->acc.x = new_acc.x;
	//output_part->acc.y = new_acc.y;
	//output_part->acc.z = new_acc.z;


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