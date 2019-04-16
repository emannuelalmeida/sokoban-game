#include "model.h" 

Model::Model() 
{ 

 
} 

void color4_to_float4(const aiColor4D *c, float f[4]) 

{ 

    f[0] = c->r; 

    f[1] = c->g; 

    f[2] = c->b; 

    f[3] = c->a; 

} 


Model::Model(char * file){ 

    Assimp::Importer importer; 
    importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 3); 

      scene = importer.ReadFile( file, 
            aiProcess_CalcTangentSpace       | 
            aiProcess_Triangulate            | 
            aiProcess_JoinIdenticalVertices  | 
            aiProcess_SortByPType            | 
            aiProcess_GenNormals); 

      double topx = 0; 
      double topy = 0; 
      double topz = 0; 
      double bottomx = 0; 
      double bottomy = 0; 
      double bottomz = 0; 

      if( !scene) 
      { 

          printf("Erro de leitura : %s", importer.GetErrorString()); 

      } else { 

          all = new vector<Triangle* >; 

          for (unsigned int i = 0; i< scene->mNumMeshes; i++) { 

              if (scene->HasMaterials()){ 

                  Material *mtl = new Material(); 
                  float temp[4]; 
                  unsigned int max; 
                  aiColor4D tempColor; 

                  if(AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], AI_MATKEY_COLOR_DIFFUSE, &tempColor)){ 
 
                          mtl->hasDiffuse = true; 
                          color4_to_float4(&tempColor, temp); 
                          memcpy(mtl->diffuse, temp, 4 * sizeof(float)); 

                  } 

                  if(AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], AI_MATKEY_COLOR_AMBIENT, &tempColor)){ 

                          mtl->hasAmbient = true; 
                          color4_to_float4(&tempColor, temp); 
                          memcpy(mtl->ambient, temp, 4 * sizeof(float)); 

                  } 

                  if(AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], AI_MATKEY_COLOR_SPECULAR, &tempColor)){ 

                          mtl->hasSpecular = true; 
                          color4_to_float4(&tempColor, temp); 
                          memcpy(mtl->specular, temp, 4 * sizeof(float)); 

                  } 

                  if(AI_SUCCESS == aiGetMaterialColor(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], AI_MATKEY_COLOR_EMISSIVE, &tempColor)){ 

                          mtl->hasEmission = true; 
                          color4_to_float4(&tempColor, temp); 
                          memcpy(mtl->emission, temp, 4 * sizeof(float)); 


                  } 

                  float shineness, strenght; 

                  max = 1; 

                  int ret1 = aiGetMaterialFloatArray(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], AI_MATKEY_SHININESS, &shineness, &max); 

                  max = 1; 

                  int ret2 = aiGetMaterialFloatArray(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], AI_MATKEY_SHININESS_STRENGTH, &strenght, &max); 

                  if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS)){ 

                      mtl->shineness = shineness * strenght; 


                  }else { 
 
                      mtl->shineness = 0; 

                  } 

                  mats.push_back(mtl); 

              } 


              for (unsigned int j = 0; j < scene->mMeshes[i]->mNumFaces; j++){ 

                  Vertex tempVx1; 
                  Vertex tempVx2; 
                  Vertex tempVx3; 

                  tempVx1.x = scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[0]].x; 
                  tempVx1.z = scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[0]].y; 
                  tempVx1.y = -scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[0]].z; 

                  tempVx1.nX = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[0]].x; 
                  tempVx1.nZ = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[0]].y; 
                  tempVx1.nY = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[0]].z; 

                  if ((  tempVx1.x) > topx) topx =   tempVx1.x; 
                  if ((  tempVx1.y) > topy) topy =   tempVx1.y; 
                  if ((  tempVx1.z) > topz) topz =   tempVx1.z; 

                  if ((  tempVx1.x) < bottomx) bottomx =   tempVx1.x; 
                  if ((  tempVx1.y) < bottomy) bottomy =   tempVx1.y; 
                  if ((  tempVx1.z) < bottomz) bottomz =   tempVx1.z; 

                  tempVx2.x = scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[1]].x; 
                  tempVx2.z = scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[1]].y; 
                  tempVx2.y = -scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[1]].z; 

                  tempVx2.nX = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[1]].x; 
                  tempVx2.nZ = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[1]].y; 
                  tempVx2.nY = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[1]].z; 

                  if ((  tempVx2.x) > topx) topx =   tempVx2.x; 
                  if ((  tempVx2.y) > topy) topy =   tempVx2.y; 
                  if ((  tempVx2.z) > topz) topz =   tempVx2.z; 

                  if ((  tempVx2.x) < bottomx) bottomx =   tempVx2.x; 
                  if ((  tempVx2.y) < bottomy) bottomy =   tempVx2.y; 
                  if ((  tempVx2.z) < bottomz) bottomz =   tempVx2.z; 

                  tempVx3.x = scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[2]].x; 
                  tempVx3.z = scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[2]].y; 
                  tempVx3.y = -scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[2]].z; 

                  tempVx3.nX = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[2]].x; 
                  tempVx3.nZ = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[2]].y; 
                  tempVx3.nY = scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[j].mIndices[2]].z; 

                  if ((  tempVx3.x) > topx) topx =   tempVx3.x; 
                  if ((  tempVx3.y) > topy) topy =   tempVx3.y; 
                  if ((  tempVx3.z) > topz) topz =   tempVx3.z; 

                  if ((  tempVx3.x) < bottomx) bottomx =   tempVx3.x; 
                  if ((  tempVx3.y) < bottomy) bottomy =   tempVx3.y; 
                  if ((  tempVx3.z) < bottomz) bottomz =   tempVx3.z; 

                  Triangle *tg = new Triangle(); 

                  tg->points[0] = tempVx1; 
                  tg->points[1] = tempVx2; 
                  tg->points[2] = tempVx3; 
                  tg->matIndex = scene->mMeshes[i]->mMaterialIndex; 

                  all->push_back(tg); 

             } 

      } 
      } 

      sizex = (int) (topx - bottomx); 
      sizey = (int) (topy - bottomy); 
      sizez = (int) (topz - bottomz); 


      for (int i = 0; i < all->size(); i++){ 

          if (bottomx < 0) { 
              all->at(i)->points[0].x += -bottomx; 
              all->at(i)->points[1].x += -bottomx; 
              all->at(i)->points[2].x += -bottomx; 
          } 

          if (bottomy < 0) { 
              all->at(i)->points[0].y += -bottomy; 
              all->at(i)->points[1].y += -bottomy; 
              all->at(i)->points[2].y += -bottomy; 
          } 

          if (bottomz < 0) { 
              all->at(i)->points[0].z += -bottomz; 
              all->at(i)->points[1].z += -bottomz; 
              all->at(i)->points[2].z += -bottomz; 
          } 

      } 

} 

vector<Triangle* > *Model::getAllTriangles(){ 
    return all; 
} 

unsigned int Model::getSizeX(){ 
    return sizex; 
} 

unsigned int Model::getSizeY(){ 
    return sizey; 
} 

unsigned int Model::getSizeZ(){ 
    return sizez; 
} 

Material *Model::getMaterial(int indx){ 
    return mats[indx]; 
} 

void Model::setMaterial(Material *mat, unsigned int idx){ 

    mats.at(idx) = mat; 

} 
