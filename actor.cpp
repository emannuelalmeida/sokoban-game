#include "actor.h" 

Actor::Actor(unsigned int _ID, int _posx, int _posy, int _posz, unsigned int _sizex, unsigned int _sizey, unsigned int _sizez, unsigned int _dir) 
{ 
    ID = _ID; 
    posx = _posx; 
    posy = _posy; 
    posz = _posz; 
    sizex = _sizex; 
    sizey = _sizey; 
    sizez = _sizez; 
    alive = true; 
    isGravAffec = false; 
    direction = _dir; 
    aim = 0; 
    falling = false; 
    jumpRest = 0; 
    isNPC = true; 
    matIdx = -1; 
    //O primeiro polígono por padrão é do tamanho do objeto, sendo que suas posições são relativas ao centro do objeto. 
    Polygon pol1; 

    pol1.posx = 0; 
    pol1.posy = 0; 
    pol1.posz = 0; 
    pol1.sizex = sizex; 
    pol1.sizey = sizey; 
    pol1.sizez = sizez; 
    speed = 1; 
    parts.push_back(pol1); 

    setDinamic(true); 


} 

void Actor::addPolygon(int _posx, int _posy, int _posz, unsigned int _sizex, unsigned int _sizey, unsigned int _sizez){ 

    Polygon pol; 

    pol.posx = _posx; 
    pol.posy = _posy; 
    pol.posz = _posz; 
    pol.sizex = _sizex; 
    pol.sizey = _sizey; 
    pol.sizez = _sizez; 

    parts.push_back(pol); 

} 

Model *Actor::getModel(){ 
    return mod; 
} 

void Actor::setModel(Model *_mod){ 

    mod = _mod; 
    sizex = mod->getSizeX(); 
    sizey = mod->getSizeY(); 
    sizez = mod->getSizeZ(); 

    parts[0].sizex = sizex; 
    parts[0].sizey = sizey; 
    parts[0].sizez = sizez; 

    hasMtl = true; 

} 

unsigned int Actor::getPolygonNum(){ 
    return parts.size(); 
} 

Polygon Actor::getPolygon(int i){ 
    return parts[i]; 
} 

void Actor::setAlive(bool _alive){ 
    alive = _alive; 
} 

bool Actor::getAlive(){ 
    return alive; 
} 

void Actor::setID(unsigned int _ID){ 
    ID = _ID; 
} 

void Actor::setJumpRest(int i){ 
    jumpRest = i; 
} 

int Actor::getJumpRest(){ 
    return jumpRest; 
} 

bool Actor::getFalling(){ 
    return falling; 
} 

void Actor::setFalling(bool fall){ 
    falling = fall; 
} 

Material *Actor::getMaterial(unsigned int idx){ 

    return mod->getMaterial(idx); 

} 

void Actor::setMaterialWithIndex(Material * mat, unsigned int idx){ 

    mod->setMaterial(mat, idx); 

} 