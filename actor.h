#ifndef ACTOR_H 
#define ACTOR_H 

#include"mapelement.h" 
#include"model.h" 


class Actor : public MapElement 
{ 
public: 
    Actor(unsigned int, int _posx, int _posy, int _posz, unsigned int _sizex, unsigned int _sizey, unsigned int _sizez, unsigned int); 
    ~Actor(); 

    void addPolygon(int, int, int, unsigned int, unsigned int, unsigned int); 
    unsigned int getPolygonNum(); 
    Polygon getPolygon(int i); 
    Model *getModel(); 
    void setModel(Model *); 

    void setAlive(bool _alive); 
    bool getAlive(); 
    void setID(unsigned int _ID); 
    int getJumpRest(); 
    void setJumpRest(int i); 
    bool getFalling(); 
    void setFalling(bool fall); 
    Material *getMaterial(unsigned int); 
    void setMaterialWithIndex(Material *, unsigned int); 

private: 
    bool alive; 
    vector<Polygon> parts; 
    bool falling; 
    int jumpRest; 
    Model *mod; 


}; 

#endif // ACTOR_H
