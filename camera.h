#ifndef CAMERA_H 
#define CAMERA_H 
 
class Camera 
{ 
public: 
    //A câmera padrão é a câmera de primeira pessoa. 
    Camera(); 
    Camera(unsigned int, int _height, int _distance, int); 

    unsigned int getCameraNum(); 
    int getHeight(); 
    int getDistance(); 
    int getDirection(); 

    void mudaParametros(int sumHeight, int sumDistance, int sumDirection); 

private: 
    unsigned int num; 
    int height; 
    int distance; 
    int direction; 

}; 

#endif // CAMERA_H
