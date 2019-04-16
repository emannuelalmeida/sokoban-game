#ifndef PROJECTILE_H 
#define PROJECTILE_H 

#include"mapelement.h" 
#include"model.h" 

class Projectile : public MapElement 
{ 
public: 
    Projectile(int _speed, bool _friendly, int _kind, int _posx, int _posy, int _posz, int _direction, int _aim, Model *_mod); 

    bool isFriendly(); 
    int getKind(); 
    bool isDestroyed(); 
    Model *getModel(); 
    Material* getMaterial(unsigned int idx); 
    void setDestroyed(); 

private: 
    bool friendly; 
    int kind; 
    bool destroyed; 
    Model *mod; 
}; 

#endif // PROJECTILE_H
