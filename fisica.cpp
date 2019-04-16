#include"fisica.h" 


CollisionResult checkCollisionWallsSelected(MapElement *act, Wall *parede, int xmais, int ymais, int zmais){ 

    CollisionResult temp; 

    if (act->getPosx()+xmais >= parede->getPosx() && act->getPosx()+xmais <= parede->getPosx() + parede->getSizex() || act->getPosx()+xmais+act->getSizex() >= parede->getPosx() && act->getPosx()+xmais+act->getSizex() <= parede->getPosx() + parede->getSizex()){ 

            if (act->getPosy()+ymais >= parede->getPosy() && act->getPosy()+ymais <= parede->getPosy() + parede->getSizey() || act->getPosy()+ymais+act->getSizey() >= parede->getPosy() && act->getPosy()+ymais+act->getSizey() <= parede->getPosy() + parede->getSizey()){ 

                if (act->getPosz()+zmais >= parede->getPosz() && act->getPosz()+zmais <= parede->getPosz() + parede->getSizez() || act->getPosz()+zmais+act->getSizez() >= parede->getPosz() && act->getPosz()+zmais+act->getSizez() <= parede->getPosz() + parede->getSizez()) { 
                    temp.where = parede; 
                    temp.hit = true; 
                    return temp; 
                } 
            } 

    } 


    temp.hit = false; 
    return temp; 

} 

CollisionResult checkCollisionWalls(Map *map, MapElement *act, int xmais, int ymais, int zmais){ 
 
    CollisionResult temp; 

    int index = map->binarySearch(act->getPosx()+xmais); 

    if ( index < 0) { 

        temp.hit = false; 
        return temp; 

    } 

    NoParede *actual = map->getNoParede(index); 

    while (actual != NULL){ 

        temp = checkCollisionWallsSelected(act, actual->wall, xmais, ymais, zmais); 
        if (temp.hit) break; 
        actual = actual->next; 

    } 

    return temp; 

} 


CollisionResult checkCollisionActors(Map *map, MapElement *obj, int xmais, int ymais, int zmais, unsigned int _ID){ 

    CollisionResult temp; 

    for (unsigned int i = 0; i < map->getActorsNum(); i++){ 
        //Caso a ID seja a mesma, vc está checando colisão com vc mesmo... 
        if (map->getActor(i)->getID() == _ID || !map->getActor(i)->getAlive()) continue; 

        for (int j = 0; j < map->getActor(i)->getPolygonNum(); j++) if (obj->getPosy()+ymais >= map->getActor(i)->getPolygon(j).posy + map->getActor(i)->getPosy() && obj->getPosy()+ymais <= map->getActor(i)->getPolygon(j).posy + map->getActor(i)->getPosy() +  map->getActor(i)->getPolygon(j).sizey || obj->getPosy()+ymais+obj->getSizey() >= map->getActor(i)->getPolygon(j).posy + map->getActor(i)->getPosy() && obj->getPosy()+ymais+obj->getSizey() <= map->getActor(i)->getPolygon(j).posy + map->getActor(i)->getPosy() + map->getActor(i)->getPolygon(j).sizey){ 

            if (obj->getPosx()+xmais >= map->getActor(i)->getPolygon(j).posx + map->getActor(i)->getPosx() && obj->getPosx()+xmais <= map->getActor(i)->getPolygon(j).posx + map->getActor(i)->getPosx() + map->getActor(i)->getPolygon(j).sizex || obj->getPosx()+xmais+obj->getSizex() >= map->getActor(i)->getPolygon(j).posx + map->getActor(i)->getPosx() && obj->getPosx()+xmais+obj->getSizex() <= map->getActor(i)->getPolygon(j).posx + map->getActor(i)->getPosx() + map->getActor(i)->getPolygon(j).sizex){ 

                if (obj->getPosz()+zmais >= map->getActor(i)->getPolygon(j).posz + map->getActor(i)->getPosz() && obj->getPosz()+zmais <= map->getActor(i)->getPolygon(j).posz + map->getActor(i)->getPosz() + map->getActor(i)->getPolygon(j).sizez || obj->getPosz()+zmais+obj->getSizez() >= map->getActor(i)->getPolygon(j).posz + map->getActor(i)->getPosz() && obj->getPosz()+zmais+obj->getSizez() <= map->getActor(i)->getPolygon(j).posz + map->getActor(i)->getPosz() + map->getActor(i)->getPolygon(j).sizez) { 
                    temp.where = map->getActor(i); 
                    temp.hit = true; 
                    return temp; 
                } 
            } 

        } 

    } 

    temp.hit = false; 
    return temp; 

} 


CollisionResult move(Map *map, MapElement *act, int action){ 

    int tempX, tempY, tempZ; 
    CollisionResult temp; 

    tempX = dirX[action][act->getDirection()]; 
    if (act->isGravityAffected()) tempY = act->getAim(); 
    else tempY = 0; 
    tempZ = dirZ[action][act->getDirection()]; 

    for (int i = 0; i < act->getSpeed(); i++){ 
        temp = checkCollisionActors(map, act, tempX, tempY, tempZ, act->getID()); 

        if (temp.hit){ 

            if (act->getDinamic() && !act->getIsNPC()){ 

                Projectile *tp = (Projectile *) act; 
                if (!tp->isFriendly() || temp.where->getID() != 0) break; 
                else { 

                    if (act->getPosy() + tempY < 1) tempY = 0; 

                    act->setPosx(tempX); 
                    act->setPosy(tempY); 
                    act->setPosz(tempZ); 

                } 

            } 


        } else { 

            temp = checkCollisionWalls(map,  act, tempX, tempY, tempZ); 
            if (temp.hit) { 

                if (temp.where->getSizey()+temp.where->getPosy() <= act->getPosy()+act->getSizey()/5){ 

                    tempY = temp.where->getSizey()+temp.where->getPosy() + 1; 

                    act->setPosx(tempX); 
                    act->setPosy(tempY); 
                    act->setPosz(tempZ); 
                    temp.hit = false; 

                } 


            } else { 

                if (act->getPosy() + tempY < 1) tempY = 0; 

                act->setPosx(tempX); 
                act->setPosy(tempY); 
                act->setPosz(tempZ); 

            } 

        } 
    } 

    //Se o movimento não foi completado alguem vai querer saber o motivo... 
    return temp; 
} 

bool jumpUp(Map *map, Actor *act){ 

    int tempX, tempY, tempZ; 

    tempX = 0; 
    tempY = 2; 
    tempZ = 0; 
    bool naoColide; 
    act->setJumpRest(act->getJumpRest() - 1); 

    naoColide = !(checkCollisionWalls(map,  act, tempX, tempY, tempZ).hit) && !(checkCollisionActors(map, act, tempX, tempY, tempZ, act->getID()).hit); 

    if (naoColide){ 

        act->setPosy(tempY); 

    } 

    //Se o movimento não foi completado alguem vai querer saber o motivo... 
    return naoColide; 
} 

bool fallDown(Map *map, Actor *act){ 

    int tempX, tempY, tempZ; 

    tempX = 0; 
    tempY = -4; 
    tempZ = 0; 
    bool naoColide; 

    naoColide = !(checkCollisionWalls(map,  act, tempX, tempY, tempZ).hit) && !(checkCollisionActors(map, act, tempX, tempY, tempZ, act->getID()).hit) && act->getPosy() > 0; 

    if (naoColide){ 

        act->setPosy(tempY); 

    } 

    //Se o movimento não foi completado alguem vai querer saber o motivo... 
    return naoColide; 
}
