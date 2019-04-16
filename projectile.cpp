#include "projectile.h" 

Projectile::Projectile(int _speed, bool _friendly, int _kind, int _posx, int _posy, int _posz, int _direction, int _aim, Model* _mod) 
{ 
    speed = _speed; 
    friendly = _friendly; 
    kind = _kind; 
    destroyed = false; 
    sizex = 2; 
    sizey = 2; 
    sizez = 2; 
    isGravAffec = true; 
    posx = _posx; 
    posy = _posy; 
    posz = _posz; 
    direction = _direction; 
    aim = _aim; 
    mod = _mod; 
    hasMtl = true; 
    dinamic = true; 
} 

bool Projectile::isFriendly(){ 
    return friendly; 
} 

int Projectile::getKind(){ 
    return kind; 
} 

bool Projectile::isDestroyed(){ 
    return destroyed; 
} 

void Projectile::setDestroyed(){ 
    destroyed = true; 
} 

Model *Projectile::getModel(){ 

    return mod; 

} 

Material *Projectile::getMaterial(unsigned int idx){ 

    return mod->getMaterial(idx); 

}
