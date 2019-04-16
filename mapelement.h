#ifndef MAPELEMENT_H 
#define MAPELEMENT_H 
#include "vector" 

using namespace std; 

enum TextureType {NONE, TEX_2D, TEX_3D,REFLECT}; 

struct Polygon { 

    int posx, posy, posz; 
    unsigned int sizex, sizey, sizez; 

}; 


struct Material { 

    float diffuse[4]; 
    float specular[4]; 
    float emission[4]; 
    float ambient[4]; 
    float shineness; 

    bool hasDiffuse = false; 
    bool hasSpecular = false; 
    bool hasEmission = false; 
    bool hasAmbient = false; 

    vector<int> textures; 

}; 

class MapElement 
{ 
public: 

    MapElement(); 

    int getDirection(); 
    int getSpeed(); 
    int getAim(); 
    bool isGravityAffected(); 
    int getPosx(); 
    int getPosy(); 
    int getPosz(); 
    unsigned int getSizex(); 
    unsigned int getSizey(); 
    unsigned int getSizez(); 
    TextureType getTextureType(); 
    int getTextIndex(); 
    unsigned int getID(); 
    bool getDinamic(); 
    Material *getMaterial(); 
    unsigned int getMaterialIndex(); 
    bool getIsNPC(); 

    void sumDirection(int soma); 
    void setSpeed(int i); 
    void setAim(int soma); 
    void setGravityAffected(bool sim); 
    void setPosx(int); 
    void setPosy(int); 
    void setPosz(int); 
    void setTextureType(TextureType); 
    void setTextIndex(int i); 
    void setDinamic(bool); 
    void setMaterial(Material *); 
    void setMaterialIndex(unsigned int); 
    bool hasMaterial(); 

protected: 
    unsigned int ID; 

    int direction; 
    int speed; 
    int aim; 
    bool isGravAffec; 
    int posx, posy, posz; 
    unsigned int sizex, sizey, sizez; 
    bool dinamic; 
    unsigned int matIdx; 

    bool hasMtl; 
    Material *mtl; 

    bool isNPC; 

    TextureType tpTx; 
    unsigned int txID; 

}; 

#endif // MAPELEMENT_H
