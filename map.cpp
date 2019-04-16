#include "Map.h" 
#include"stdio.h" 

Map::Map(char * _ID) 
{ 

    ID = _ID; 
    //ctor 
} 

Map::~Map() 
{ 

    //dtor 
} 

int Map::binarySearch(int value){ 

    int start = 0; 
    int end = walls.size(); 

    //printf("START : inicio = 0, fim = %i, valor = %i \n", fim, valor); 
    int middle; 

    while (start != end && end > start + 1){ 

        middle = (start+end)/2; 
        if (walls[middle]->value == value) return middle; 
        if (value > walls[middle]->value) start = middle; 
        else end = middle; 

    } 

    return -1; 

} 


void Map::putActor(Actor * act){ 

    actors.push_back(act); 
    actors[actors.size() - 1]->setID(actors.size() -1); 

} 

void Map::putProjectile(Projectile *proj){ 

    projectiles.push_back(proj); 

} 

void Map::putWall(Wall *wall){ 

    wallList.push_back(wall); 
    //int index = -1; 
    for (unsigned int i = 0; i < wall->getSizex(); i++){ 

        //int i = 0; 
        NoParede *no = new NoParede(); 
        no->next = NULL; 
        no->value = wall->getPosx() + i; 
        no->wall = wall; 
        int index = binarySearch(no->value); 

        if (index == -1) { 

            if (walls.size() == 0) walls.push_back(no); 
            else { 
                unsigned int count = 0; 
                while (walls[count]->value < no->value) { 
                    count++; 
                    if (walls.size() == count) break; 

                } 

                walls.insert(walls.begin() + count, no); 

            } 

        } 

        else { 

            NoParede * actual = walls[index]; 
            while (actual->next != NULL) actual = actual->next; 
            actual->next = no; 

        } 

    } 

} 

Actor * Map::getActor(int i){ 
    return actors[i]; 
} 

Projectile * Map::getProjectile(int i){ 
    return projectiles[i]; 
} 

Wall * Map::getWall(int i){ 
    return wallList[i]; 
} 

char  * Map::getID(){ 
    return ID; 
} 

unsigned int Map::getActorsNum(){ 
    return actors.size(); 
} 

unsigned int Map::getWallsNum(){ 
    return wallList.size(); 
} 

unsigned int Map::getProjectilesNum(){ 
    return projectiles.size(); 
} 

unsigned int Map::getNoParedeNum(){ 
    return walls.size(); 
} 

NoParede *Map::getNoParede(int idx){ 

    return walls[idx]; 
} 

void Map::deleteProjectile(int i){ 

    Projectile * proj; 
    proj = projectiles[i]; 
    delete proj; 
    projectiles.erase(projectiles.begin() + i); 

} 

Vertex Map::getAmbColor(){ 
    return ambColor; 
} 

void Map::setAmbColor(Vertex _amb){ 
    ambColor = _amb; 
} 
