#ifndef WALL_H 
#define WALL_H 
#include"mapelement.h" 



class Wall : public MapElement 
{ 

public: 
    Wall(unsigned int, int _posx, int _posy, int _posz, unsigned int _sizex, unsigned int _sizey, unsigned int _sizez); 
    Wall(); 

    bool getAlwaysDraw(); 
    void setAlwaysDraw(bool _draw); 

private: 
    bool alwaysDraw; 

}; 

#endif // WALL_H
