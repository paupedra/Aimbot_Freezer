#include "SDL/include/SDL.h"
#include "p2List.h"


struct Vec3d;
struct Cannon;
struct Enemy;
struct Ball;


p2List<Vec3d> Trajectory;


void Aimbot(Cannon cannon, Enemy koopa, Ball ball, float dt);
bool Collided(Vec3d* ball_pos, Vec3d* target_pos);
