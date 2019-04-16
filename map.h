#ifndef MAP_H 
#define MAP_H 

#include <string> 
#include "mapelement.h" 
#include "wall.h" 
#include "actor.h" 
#include "projectile.h" 
#include <vector> 

using namespace std; 

struct NoParede { 

    NoParede *next; 
    Wall * wall; 
    int value; 

}; 

class Map 
{ 
    public: 
    Map(char * _ID); 
    ~Map(); 
    void putActor(Actor * act); 
    void putWall(Wall *parede); 
    void putStatic(MapElement *elem); 
    void putProjectile(Projectile *proj); 

    Actor * getActor(int i); 
    Projectile * getProjectile(int i); 
    Wall * getWall(int i); 
    NoParede *getNoParede(int); 
    char  * getID(); 
    int binarySearch(int); 
    Vertex getAmbColor(); 
    void setAmbColor(Vertex); 

    unsigned int getActorsNum(); 
    unsigned int getWallsNum(); 
    unsigned int getProjectilesNum(); 
    unsigned int getNoParedeNum(); 
    void deleteProjectile(int i); 

    protected: 
    private: 

    //Armazena os objetos que se movem dentro do mapa 
    vector<Actor *> actors; 

    //Armazena as paredes que foram criadas dentro do mapa 
    vector<NoParede *> walls; 

    //Armazena as paredes para facilitar o trabalho de desenhar 
    vector<Wall *> wallList; 

    //Armaneza os projéteis ainda existentes no estado atual 
    vector<Projectile *> projectiles; 

    Vertex ambColor; 

    //void removeObject(mapelement * object); 

    char * ID; 


}; 

#endif // MAP_H
