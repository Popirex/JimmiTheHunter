#include "map.h"
#include <raylib.h>



//              ||||||||    APERTURA FILE E ESTRAZIONE BITMAP   ||||||||



void bitMapExtraction(int* y, int* x, int** bitMap, const char* mapPath){

// apro il file della mappa
    FILE* mapFile = fopen(mapPath, "r");

    // se il file descriptor è nullo eseguo exit
    if(mapFile == NULL){
        printf("ERRORE: apertura del file %s fallita\n", mapPath);
        exit(1);
    }


    // prendo le dimensioni della mappa
    getMapSize(mapFile, y, x);


    // alloco la memoria per la bitMap
    *bitMap = malloc( (*x) * (*y) * sizeof(int));


    // exit se è riscontrato un errore nell'allocazione
    if(*bitMap == NULL){
        printf("ERRORE: malloc per la bitMap Fallita\n");
        fclose(mapFile);
        exit(2);
    }

    

    // carico la bitMap dal file alla heap
    loadMap(mapFile, *bitMap, *y, *x);

    
    // chiudo il mapFile
    if( fclose(mapFile) != 0){
        printf("ERRORE: chiusura del file %s fallita\n ", mapPath);
        exit(2);
    }

}

void loadMapBlocks(const char* grassPath, const char* dirtPath, Texture2D* grass, Texture2D* dirt){

    *grass = LoadTexture(grassPath);
    *dirt = LoadTexture(dirtPath);
}

void drawMap(int bitMap[], int y, int x,  Texture2D grass, Texture2D dirt,int TILESIZE){
    

    for(int rig = 0; rig < y; rig++){

        for(int col = 0; col < x; col++){

            if(bitMap[rig*x+col] == 1){
                DrawTexture(grass, col*TILESIZE, rig*TILESIZE, WHITE);
            }

            if(bitMap[rig*x+col] == 2){
                DrawTexture(dirt, col*TILESIZE, rig*TILESIZE, WHITE);
            }

        }

    }

}



void loadMap(FILE* mapFile, int* bitMap, int y, int x){

    int arraySize = x * y;

    // leggo la bitmap della mappa
    for(int i = 0; i < arraySize ; i++){

        fscanf(mapFile, "%d", &bitMap[i]);
        
    } 
}


void getMapSize(FILE* mapFile, int* y, int* x){

    fscanf(mapFile, "%d %d", y, x);
}

void printMapData(int* bitMap, int y, int x){
    
    int size = x*y;
    printf("y: %d   x: %d   map size: %d\n", y, x, size);

    int breakPoint = 0;
    for(int i = 0; i < size; i++){
        breakPoint++;
        printf("%d ", bitMap[i]);
        if(breakPoint % x == 0) printf("\n");
    }



}