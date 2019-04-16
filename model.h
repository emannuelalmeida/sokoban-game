#ifndef MODEL_H 
#define MODEL_H 

#include <stdio.h> 
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/vector3.h> 
#include <assimp/material.h> 
#include <assimp/light.h> 
#include <assimp/texture.h> 
#include <assimp/matrix4x4.h> 
#include <assimp/postprocess.h> 
#include <vector> 
#include <mapelement.h> 

using namespace std; 

struct Vertex { 

    double x; 
    double y; 
    double z; 
    double nX; 
    double nY; 
    double nZ; 

}; 

struct Triangle { 

    Vertex points[3]; 
    unsigned int texIndex; 
    unsigned int matIndex; 

}; 


class Model 
{ 
public: 
    Model(); 
    Model(char *); 
    unsigned int getSizeX(); 
    unsigned int getSizeY(); 
    unsigned int getSizeZ(); 
    vector<Triangle* > *getAllTriangles(); 
    int getTexIndex(unsigned int); 
    Material *getMaterial(int indx); 
    void setMaterial(Material *, unsigned int); 

private: 

    const aiScene* scene; 
    unsigned int sizex; 
    unsigned int sizey; 
    unsigned int sizez; 
    vector<Material *> mats; 

    vector<Triangle* > * all; 

}; 

#endif // MODEL_H
