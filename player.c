#include "player.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#define x_friction 0.7
#define y_friction 0.9

// idle paths
const char* idleL = "rsc/playerArt/idle/player_idle_left.png";
const char* idleR = "rsc/playerArt/idle/player_idle_right.png";

//walk left paths
const char* walkL1 = "rsc/playerArt/walkL/player_walk_1_left.png";
const char* walkL2 = "rsc/playerArt/walkL/player_walk_2_left.png";
const char* walkL3 = "rsc/playerArt/walkL/player_walk_3_left.png";
const char* walkL4 = "rsc/playerArt/walkL/player_walk_4_left.png";

//walk rigth paths
const char* walkR1 = "rsc/playerArt/walkR/player_walk_1_right.png";
const char* walkR2 = "rsc/playerArt/walkR/player_walk_2_right.png";
const char* walkR3 = "rsc/playerArt/walkR/player_walk_3_right.png";
const char* walkR4 = "rsc/playerArt/walkR/player_walk_4_right.png";


//jump paths
const char* jumpL = "rsc/playerArt/jump/player_jump_left.png";
const char* jumpR = "rsc/playerArt/jump/player_jump_right.png";

// shoot paths
const char* shootR = "rsc/playerArt/shoot/player_shoot_right.png";
const char* shootL = "rsc/playerArt/shoot/player_shoot_left.png";

const float groundHeight = 600;
float gravity = 0;

void loadSkins(Player* p){

    // load idle textures
    p->idle[0] = LoadTexture(idleR);
    p->idle[1] = LoadTexture(idleL);

    // load jump textures
    p->jump[0] = LoadTexture(jumpR);
    p->jump[1] = LoadTexture(jumpL);

    // load shoot textures
    p->shoot[0] = LoadTexture(shootR);
    p->shoot[1] = LoadTexture(shootL);

    // load walkL textures
    p->walkL[0] = LoadTexture(walkL1);
    p->walkL[1] = LoadTexture(walkL2);
    p->walkL[2] = LoadTexture(walkL3);
    p->walkL[3] = LoadTexture(walkL4);

    // load walkR textures

    p->walkR[0] = LoadTexture(walkR1);
    p->walkR[1] = LoadTexture(walkR2);
    p->walkR[2] = LoadTexture(walkR3);
    p->walkR[3] = LoadTexture(walkR4);


}

void initializePlayer(Player* p, float WIDTH, float HEIGHT, float TILESIZE){
    p->pos = (Vector2){ WIDTH/2  , HEIGHT - (5*TILESIZE)  };

    p->vel = Vector2Zero();
    
    p->acc = Vector2Zero();

    p->orientation = 0;

    p->step = 0;

    p->shooting = false;
}

void updatePlayer(Player* p){

    p->acc = (Vector2){p->acc.x * x_friction, (p->acc.y*y_friction) + gravity};
    p->vel = Vector2Add(p->vel, p->acc);
    p->vel = (Vector2){p->vel.x*x_friction, p->vel.y*y_friction};
    p->pos = Vector2Add(p->pos, p->vel);

    if(p->pos.y > groundHeight){
        p->pos.y = groundHeight;
        p->acc.y = 0;
        p->vel.y = 0;
        gravity = 0;
    }

    if(p->vel.x ==  0 ) p->step = 0;

}

void movePlayer(Player* p){
    if(IsKeyDown(KEY_D)){
        p->orientation = 0;
        p->acc.x+=1;
    }
    else if (IsKeyDown(KEY_A)) {
        p->orientation = 1;
        p->acc.x -= 1;
    }

    if (IsKeyDown(KEY_SPACE) && (int)(p->pos.y) == groundHeight) {
        p->acc.y -= 8;
        gravity = 1;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        p->shooting = true;
    }
    else{
        p->shooting = false;
    }

}

void drawPlayer(Player* p){


    int velRel = (int)(p->vel.x + p->vel.y); 

    if(p->shooting){
        DrawTexture(p->shoot[p->orientation], (int)p->pos.x , (int)p->pos.y, WHITE);
    }
    else if( ((int)(p->vel.x) == 0) && ((int)(p->vel.y) == 0) ){
        DrawTexture(p->idle[p->orientation], (int)p->pos.x , (int)p->pos.y, WHITE);
    }
    else if(p->vel.x > 0 && p->pos.y == groundHeight){
        int index = p->step % 4;
        DrawTexture(p->walkR[index], (int)p->pos.x , (int)p->pos.y, WHITE);
        p->step++;
    }
    else if(p->vel.x < 0 && p->pos.y == groundHeight){
        int index = p->step % 4;
        DrawTexture(p->walkL[index], (int)p->pos.x , (int)p->pos.y, WHITE);
        p->step++;
    }
    else if(p->pos.y != groundHeight){
        DrawTexture(p->jump[p->orientation], (int)p->pos.x , (int)p->pos.y, WHITE);
    }
}

void printPlayerInfo(Player* p){
    printf("pos: {%f, %f}   -   vel: {%f, %f}   -   acc: {%f, %f}\n", p->pos.x, p->pos.y, p->vel.x, p->vel.y, p->acc.x, p->acc.y);
}