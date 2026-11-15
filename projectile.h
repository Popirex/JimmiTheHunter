#include "map.h"
#include "player.h"
#include <raylib.h>

typedef struct{
    Vector2 pos;
    Vector2 endPoint;
    Vector2 vel;
    bool state;
    float radius;
    bool hitBoxActivate;
    Rectangle hitBox;
}Projectile;

void allocateProjectiles(Projectile** prs);

void createProjectile(Player* p, Projectile** prs, Vector2 mousePos);

void printProjectiles(Projectile* prs);

void moveProjectile(Projectile** prs);

bool projectileIsIn(Projectile* prs);

void playerShooting(Player* p, Projectile** pr);

void drawProjectiles(Projectile** pr);

bool checkPossibleShot(Player* p, Vector2 mousePos);

void updateHitBox(Projectile* pr);