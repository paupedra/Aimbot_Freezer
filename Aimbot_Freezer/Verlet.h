struct Vec3d
{
	Vec3d() { x = 0; y = 0; z = 0; };

	float x, y, z;
};

struct particle
{
	particle() {};
	float mass;

	Vec3d pos;
	Vec3d speed;
	Vec3d acc;
};



void Verlet(particle* prev_part, particle* output_part, Vec3d force, float dt);