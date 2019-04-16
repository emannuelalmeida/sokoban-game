#ifndef FISICA_H 
#define FISICA_H 

#include<iostream> 
#include<stdio.h> 
#include<math.h> 
#include<vector> 
#include"actor.h" 
#include"Map.h" 

//Marcam quantas unidades se percorre em cada uma das 32 direções possíveis. 

static int dirX[4][32] = 
{ 
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1}, //FRENTE 
    {0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1}, //TRÁS 
    {4, 4, 4, 4, 4, 3, 2, 1, 0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 4, 4}, //ESQUERDA 
    {-4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0, -1, -2, -3, -4, -4, -4, -4} //DIREITA 
}; 

static int dirZ[4][32] = 
{ 
    {4, 4, 4, 4, 4, 3, 2, 1, 0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 4, 4}, //FRENTE 
    {-4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0, -1, -2, -3, -4, -4, -4, -4}, //TRÁS 
    {0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1}, //ESQUERDA 
    {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0, -1, -2, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -2, -1} //DIREITA 

}; 

struct CollisionResult { 

    bool hit; 
    MapElement * where; 
    bool open; 

}; 


CollisionResult move(Map *map, MapElement *act, int action); 

bool jumpUp(Map *map, Actor *act); 

bool fallDown(Map *map, Actor *act); 


CollisionResult checkCollisionActors(Map *map, MapElement *obj, int xmais, int ymais, int zmais, unsigned int _ID); 

CollisionResult checkCollisionWalls(Map *map, MapElement *act, int xmais, int ymais, int zmais); 


#endif // FISICA_H
