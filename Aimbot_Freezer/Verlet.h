#include "SDL/include/SDL.h"
#include "SDL/include/SDL_rect.h"

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

struct Ball
{
	SDL_Rect rect;    // position in the texture
	SDL_Rect ballCollider;
	SDL_Texture *tex; // texture
	float x, y;       // position in the world
	Vec3d speed;     // velocity in the world
	bool enabled;
};

struct Cannon
{
	SDL_Rect rect;    // cannon position in the texture
	SDL_Rect standRect;    // stand
	SDL_Texture* tex; // texture
	float x, y;       // position in the world
	float angle;	// rotation angle
};

struct Enemy
{
	SDL_Rect koopaRect;    // cannon position in the texture
	SDL_Rect koopaCollider;
	SDL_Texture* tex; // texture
	float x, y;       // position in the world
};


void Verlet(particle* prev_part, particle* output_part, Vec3d force, float dt);