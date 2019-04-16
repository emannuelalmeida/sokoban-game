#include "wall.h" 

Wall::Wall(unsigned int _ID, int _posx, int _posy, int _posz, unsigned int _sizex, unsigned int _sizey, unsigned int _sizez) 
{ 
    ID = _ID; 
    posx = _posx; 
    posy = _posy; 
    posz = _posz; 
    sizex = _sizex; 
    sizey = _sizey; 
    sizez = _sizez; 
    alwaysDraw = false; 
    setDinamic(false); 

} 

Wall::Wall(){ 

} 

bool Wall::getAlwaysDraw(){ 
    return alwaysDraw; 
} 

void Wall::setAlwaysDraw(bool _draw){ 
    alwaysDraw = _draw; 
} 