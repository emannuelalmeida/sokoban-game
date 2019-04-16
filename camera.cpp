#include "camera.h" 

Camera::Camera() 
{ 
    num = 0; 
    height = 0; 
    distance = 0; 
    direction = 0; 

} 

Camera::Camera(unsigned int _num, int _height, int _distance, int _direction){ 

    num = _num; 
    height = _height; 
    distance = _distance; 
    direction = _direction; 

} 

int Camera::getHeight(){ 
    return height; 
} 

int Camera::getDistance(){ 
    return distance; 
} 

int Camera::getDirection(){ 
    return direction; 
} 
 
void Camera::mudaParametros(int sumHeight, int sumDistance, int sumDirection){ 
    height += sumHeight; 
    if (height < 0) height = 0; 

    distance += sumDistance; 
    if (distance < 0) distance = 0; 

    direction += sumDirection; 
    if (direction > 31) direction -= 32; 
    if (direction < 0) direction += 32; 


} 
