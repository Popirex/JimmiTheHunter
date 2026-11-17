#include "projectile.h"
#include <raylib.h>
#include <raymath.h>

#define MAX_PROJECTILE_COUNT 500
#define pr_radius 3
#define PROJECTILE_SPEED 10
const bool hitBoxActivate = false;


void allocateProjectiles(Projectile** prs){
    //alloco memoria heap per i proiettili
    *prs = malloc(sizeof(Projectile) * MAX_PROJECTILE_COUNT);


    // exit se riscontro errori nella malloc
    if(*prs == NULL){
        printf("ERRORE: malloc per i projectiles fallita\n");
        exit(4);
    }
    // inizializzo lo stato di tutti i proiettili
    Projectile* p;
    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        p = &(*prs)[i];
        p->state = false;
        p->radius = pr_radius;
        p->hitBoxActivate = hitBoxActivate;
        updateHitBox(p);

    }
}

bool createProjectile(Player *p, Projectile** prs, Vector2 mousePos){
    int x_off = 0;
    int y_off = 20;


    if(p->orientation == 0){
        x_off = 40;
    }

    Vector2 start = (Vector2){p->pos.x + x_off, p->pos.y + y_off};
    Vector2 dir = Vector2Subtract(mousePos, start);

    if(Vector2Length(dir) < 0.001f) return false;

    dir = Vector2Normalize(dir);


    Projectile* pr;
    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        pr = &(*prs)[i];

        if(!pr->state){
            pr->pos = start;
            pr->endPoint = mousePos;
            pr->vel = Vector2Scale(dir, PROJECTILE_SPEED);
            pr->state = true;
            return true;
        }

        
    }
    return false;

}

void printProjectiles(Projectile* prs){

    for(int i = 0; i < MAX_PROJECTILE_COUNT; i++){
        printf("pos: {%f, %f    }     -   vel: {%f, %f}     -   state: { %d }\n", prs[i].pos.x, prs[i].pos.y, prs[i].vel.x, prs[i].vel.y, prs[i].state);
    }

}

void moveProjectile(Projectile** prs, int* aPr){
    Projectile* pr;
    int checked = 0;
    int skipped = 0;
    int deleted = 0;
    
    while(checked < (*aPr)){
        pr = &(*prs)[checked + skipped];
        // salto i proiettili non attivi
        if(!pr->state){
            skipped++;
            continue;
        }
        pr->pos = Vector2Add(pr->pos, pr->vel);
        updateHitBox(pr);
        pr->state = projectileIsIn(pr);
        if(!pr->state) deleted++;
        checked++;
    }
    (*aPr) -= deleted;

}

bool projectileIsIn(Projectile* pr){
    // if in the map the states becomes true and the projectile is still used 
    if(pr->pos.x < 1280 && pr->pos.x > 0 && pr->pos.y > 0 && pr->pos.y <= 620 ) return true;
    return false;
}

void playerShooting(Player* p, Projectile** pr, int* aPr){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && checkPossibleShot(p, GetMousePosition())) {
        p->shooting = true;
        if(createProjectile(p, pr, GetMousePosition())) (*aPr)++;
    }
    else{
        p->shooting = false;
    }
}

void drawProjectiles(Projectile** pr, int aPr){
    Projectile* p;
    int checked = 0;
    int skipped = 0;

    while( checked < aPr){
        p = &(*pr)[checked + skipped];
        if(!p->state){
            skipped++;
            continue;
        }
        DrawCircleV(p->pos, p->radius, GRAY);
        if(p->hitBoxActivate) DrawRectangleLinesEx(p->hitBox, 1, RED);  
        checked++;
    }
}

bool checkPossibleShot(Player* p, Vector2 mousePos){
    int x_off = 40;
    // verifico subito se il mouse è davanti al gicatore ( non può sparare dalla schiena)
    if((p->orientation == 0) && (mousePos.x > p->pos.x + x_off) ) return true;
    else if((p->orientation == 1) && (mousePos.x < p->pos.x) ) return true;
    else{
        return false;
    }
}

void updateHitBox(Projectile* pr){
    pr->hitBox = (Rectangle){
        pr->pos.x - pr->radius,
        pr->pos.y - pr->radius,
        pr->radius * 2,
        pr->radius * 2
    };
}