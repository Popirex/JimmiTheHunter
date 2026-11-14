#include "map.h"
#include <raylib.h>

typedef struct{

    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    Texture2D idle[2];
    Texture2D walkL[4];
    Texture2D walkR[4];
    Texture2D jump[2];
    Texture2D shoot[2];
    Rectangle hitBox;
    int orientation;
    int step;
    bool shooting;

} Player;

void loadSkins(Player* p);

void initializePlayer(Player* p, float WIDTH, float HEIGHT);

void movePlayer(Player* p);

void updatePlayer(Player* p);

void drawPlayer(Player* p);

void drawPlayerHitBox(Player* p);

void printPlayerInfo(Player* p);