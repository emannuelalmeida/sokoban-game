#include "mapelement.h" 

MapElement::MapElement() 
{ 
    tpTx = NONE; 
    txID = -1; 
    hasMtl = false; 
    isNPC = false; 

} 

int MapElement::getDirection(){ 
    return direction; 
} 

int MapElement::getSpeed(){ 
    return speed; 
} 

int MapElement::getAim(){ 
    return aim; 
} 

bool MapElement::isGravityAffected(){ 
    return isGravAffec; 
} 

int MapElement::getPosx(){ 
    return posx; 
} 

int MapElement::getPosy(){ 
    return posy; 
} 

int MapElement::getPosz(){ 
    return posz; 
} 

unsigned int MapElement::getSizex(){ 
    return sizex; 
} 

unsigned int MapElement::getSizey(){ 
    return sizey; 
} 

unsigned int MapElement::getSizez(){ 
    return sizez; 
} 

TextureType MapElement::getTextureType(){ 
    return tpTx; 
} 

int MapElement::getTextIndex(){ 
    return txID; 
} 

unsigned int MapElement::getID(){ 
    return ID; 
} 

void MapElement::sumDirection(int sum){ 
    direction += sum; 
    if (direction > 31) direction -= 32; 
    if (direction < 0) direction += 32; 
} 

void MapElement::setSpeed(int i){ 
    speed = i; 
} 

void MapElement::setAim(int soma){ 
    aim += soma; 
    if (aim > 5) aim = 5; 
    if (aim < -5) aim = -5; 
} 

void MapElement::setGravityAffected(bool sim){ 
    isGravAffec = sim; 
} 

void MapElement::setPosx(int sum){ 
    posx += sum; 
} 

void MapElement::setPosy(int sum){ 
    posy += sum; 
} 

void MapElement::setPosz(int sum){ 
    posz += sum; 
} 

void MapElement::setTextureType(TextureType tp){ 
    tpTx = tp; 
} 

void MapElement::setTextIndex(int i){ 
    txID = i; 
} 

bool MapElement::getDinamic(){ 
    return dinamic; 
} 

void MapElement::setDinamic(bool _din){ 
    dinamic = _din; 
} 

void MapElement::setMaterial(Material * _mtl){ 
    mtl = _mtl; 
    hasMtl = true; 
} 

void MapElement::setMaterialIndex(unsigned int idx){ 

    matIdx = idx; 

} 

unsigned int MapElement::getMaterialIndex(){ 

    return matIdx; 

} 

Material *MapElement::getMaterial(){ 
    return mtl; 
} 

bool MapElement::hasMaterial(){ 
    return hasMtl; 
} 

bool MapElement::getIsNPC(){ 

    return isNPC; 

} 
