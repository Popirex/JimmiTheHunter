#include "projectile.h"
#include <raylib.h>
#include <raymath.h>

#define MAX_PROJECTILE_COUNT 500
#define pr_width 8
#define pr_height 3
#define PROJECTILE_SPEED 100


void allocateProjectiles(Projectile** prs){
    //alloco memoria heap per i proiettili
    *prs = malloc(sizeof(Projectile) * MAX_PROJECTILE_COUNT);


    // exit se riscontro errori nella malloc
    if(*prs == NULL){
        printf("ERRORE: malloc per i projectiles fallita\n");
        exit(4);
    }
    // inizializzo lo stato di tutti i proiettili
    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        (*prs)[i].state = false;
    }
}

void createProjectile(Player *p, Projectile** prs, Vector2 mousePos){

    int x_off = 0;
    int y_off = 20;

    if(p->orientation == 0){
        x_off = 40;
    }

    Vector2 start = (Vector2){p->pos.x + x_off, p->pos.y + y_off};
    Vector2 dir = Vector2Subtract(mousePos, start);

    if(Vector2Length(dir) < 0.001f) return;

    dir = Vector2Normalize(dir);



    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        Projectile* pr = &(*prs)[i];

        if(!pr->state){
            pr->pos = start;
            pr->endPoint = mousePos;
            pr->vel = Vector2Scale(dir, PROJECTILE_SPEED);
            pr->state = true;
            break;
        }

        
    }

}

void printProjectiles(Projectile* prs){

    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        printf("pos: {%f, %f    }     -   vel: {%f, %f}     -   state: { %s }\n", prs[i].pos.x, prs[i].pos.y, prs[i].vel.x, prs[i].vel.y, prs[i].state?"true":"false");
    }

}

void moveProjectile(Projectile** prs){
    float dt = GetFrameTime();
    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        Projectile* pr = &(*prs)[i];
        // salto i proiettili non attivi
        if(!pr->state) continue;
        pr->pos = Vector2Add(pr->pos, Vector2Scale(pr->vel, dt));
    }
}

void checkProjectileLife(Projectile** prs){
    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        Projectile* pr = &(*prs)[i];

        if(!pr->state) continue;

        if((pr->pos.x > 1280 || pr->pos.x < 0) || (pr->pos.y < 0 || pr->pos.y > 600 )) pr->state = false;

    }
}

void PlayerShooting(Player* p, Projectile** pr){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        p->shooting = true;
        createProjectile(p, pr, GetMousePosition());
    }
    else{
        p->shooting = false;
    }
}