#include "map.h"
#include "projectile.h"
#include <raylib.h>

#define WIDTH 1200
#define HEIGHT 800
#define TILESIZE 40

const char* mapPath = "rsc/maps/mappaTest.txt";
const char* grassPath = "rsc/textures/grass.png";
const char* dirtPath = "rsc/textures/dirt.png";




int main(){


    // variabili 
    int y, x;
    int* bitMap = NULL;
    Projectile* projectiles = NULL;
    Texture2D grass, dirt;
    Player player;

    initializePlayer(&player, WIDTH, HEIGHT);






    // carico la bitMap dal file

    bitMapExtraction( &y, &x, &bitMap, mapPath);

    // alloco la memoria per i proiettili
    allocateProjectiles(&projectiles);



    

    InitWindow(WIDTH   , HEIGHT, "Popirex - Jimmy The Hunter");


    // carico le textures
    loadMapBlocks(grassPath, dirtPath, &grass, &dirt);

    loadSkins(&player);



    SetTargetFPS(15);


    while (!WindowShouldClose())
    {

        // move & update player position
        movePlayer(&player);
        playerShooting(&player, &projectiles);
        updatePlayer(&player);

        //

        // move & update projectiles position;
        moveProjectile(&projectiles);

        BeginDrawing();
            ClearBackground(SKYBLUE);
            drawMap(bitMap, y, x, grass, dirt, TILESIZE);
            drawPlayer(&player);
            drawPlayerHitBox(&player);
            drawProjectiles(&projectiles);
            //printPlayerInfo(&player);

            
        EndDrawing();
    }

    //printMapData(bitMap, y, x);
    //printProjectiles(projectiles);
    return EXIT_SUCCESS;
}