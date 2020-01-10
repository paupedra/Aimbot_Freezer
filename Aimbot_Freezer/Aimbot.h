#include "SDL/include/SDL.h"
#include "p2List.h"

struct Vec3d;
struct Cannon;
struct Enemy;
struct Ball;

Vec3d* Aimbot(Cannon cannon, Enemy koopa, Ball ball, float dt, Vec3d windForce);
bool Collided(Vec3d* ball_pos, Vec3d* target_pos);
