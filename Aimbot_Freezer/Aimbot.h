#include "SDL/include/SDL.h"

struct Vec3d;
struct Cannon;
struct Enemy;

void Aimbot(Cannon cannon, Enemy koopa, Ball ball, float dt);
bool Collided(Vec3d* ball_pos, Vec3d* target_pos);
