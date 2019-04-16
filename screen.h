#ifndef SCREEN_H 
#define SCREEN_H 
#include <SDL/SDL.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <SDL/SDL_image.h> 
#include <SDL/SDL_opengl.h> 
#include <vector> 
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include "mapelement.h" 
#include "Map.h" 
#include "camera.h" 
#include "math.h" 
#include "actor.h" 
#include "fisica.h" 


typedef struct { 

    GLuint id; 

} Texture2D; 

class Screen 
{ 
public: 

    Screen(); 
    void startScreen(); 
    void setParameters(int, int, int); 

    void drawStaticObject(MapElement *); 
    void drawObject(MapElement *); 
    void drawDinamicObject(MapElement *); 
    void updateScreen(Map *actual, Actor *hero); 
    void setCamera(unsigned int); 
    void addCamera(Camera *cam); 
    void setParameterActualCamera(); //fazer 
    void setFullScreen(); 
    int add2DTexture(char *path); 
    void setAmbientColor(Vertex); 

    void enableFog(float start, float end); 
    void disableFog(); 
    void setFogParameters(float *color, float dens, bool hitBetter, float start, float end); 

    SDL_Surface * getMainSurface(); 
    unsigned int getActualCameraIndex(); 
    Camera * getCamera(int i); 

private: 

    Texture2D *load2DTextureFromFile(char *path); 
    SDL_Surface * main, * osd, * menu; 
    int width, height, depth; 
    unsigned int actualCamera; 
    std::vector<Camera*> cams; 
    bool fullScreen; 
    GLfloat light_ambient[4]; 
    void applyMaterial(Material *mat); 
    void applyNullMaterial(); 

}; 

#endif // SCREEN_H
