#include "map.h"
#include "player.h"
#include <raylib.h>

typedef struct{
    Vector2 pos;
    Vector2 endPoint;
    Vector2 vel;
    bool state;
    int width, height;
}Projectile;

void allocateProjectiles(Projectile** prs);

void createProjectile(Player* p, Projectile** prs, Vector2 mousePos);

void printProjectiles(Projectile* prs);

void moveProjectile(Projectile** prs);

void checkProjectileLife(Projectile** prs);

void PlayerShooting(Player* p, Projectile** pr);