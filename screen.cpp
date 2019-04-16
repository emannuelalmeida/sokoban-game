#include "screen.h" 

Screen::Screen() 
{ 
    actualCamera = 0; 
    fullScreen = true; 

} 

void Screen::startScreen(){ 

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 ); 
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 ); 
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 ); 
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 ); 
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); 

    main = SDL_SetVideoMode(width, height, depth, SDL_OPENGL | SDL_FULLSCREEN); 
    if ( main == NULL ) { 
        fprintf(stderr, "Impossível executar modo de vídeo selecionado. Abortando."); 
        exit(1); 
    } 

    glShadeModel( GL_SMOOTH ); 
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 }; 
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ); 

    glClearColor( 0, 0, 0, 0 ); 

    glViewport( 0, 0, width, height ); 

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
    gluPerspective(45, width/height, 1, 300); 
    Camera *pad = new Camera(); 
    addCamera(pad); 

} 

void Screen::setParameters(int _wid, int _hei, int _dep){ 
    width = _wid; 
    height = _hei; 
    depth = _dep; 
} 

void Screen::drawStaticObject(MapElement *obj){ 

    if (obj->hasMaterial()) applyMaterial(obj->getMaterial()); 
    else applyNullMaterial(); 

    if (obj->getTextureType() == TEX_2D){ 

        glEnable(GL_TEXTURE_2D); 
        glBindTexture(GL_TEXTURE_2D, obj->getTextIndex()); 

    } 

    else if (obj->getTextureType() == REFLECT ){ 
        //Not working properly yet 

    } 

        glBegin(GL_QUADS); //Face de baixo 
            glNormal3f(0.0, -1.0, 0.0); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, 0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy(), obj->getPosz()+obj->getSizez()); // Troquei com o de baixo 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, 0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy(), obj->getPosz()); 
        glEnd(); 

        glBegin(GL_QUADS); //Face de cima 
            glNormal3f(0.0, 1.0, 0.0); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, 0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy()+obj->getSizey(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy()+obj->getSizey(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy()+obj->getSizey(), obj->getPosz()+obj->getSizez()); // Troquei com o de baixo 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, 0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy()+obj->getSizey(), obj->getPosz()); 
        glEnd(); 

        glBegin(GL_QUADS); //Face da esquerda 
            glNormal3f(-1.0, 0.0, 0.0); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, 0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizey()/100.0, 0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy()+obj->getSizey(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizey()/100.0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy()+obj->getSizey(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy(), obj->getPosz()+obj->getSizez()); 
        glEnd(); 

        glBegin(GL_QUADS); //Face da direita 
            glNormal3f(1.0, 0.0, 0.0); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, 0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizey()/100.0, 0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy()+obj->getSizey(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizey()/100.0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy()+obj->getSizey(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, obj->getSizez()/100.0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy(), obj->getPosz()+obj->getSizez()); 
        glEnd(); 

        glBegin(GL_QUADS); //Face da frente 
            glNormal3f(0.0, 0.0, -1.0); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, 0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, 0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, obj->getSizey()/100.0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy()+obj->getSizey(), obj->getPosz()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, obj->getSizey()/100.0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy()+obj->getSizey(), obj->getPosz()); 
        glEnd(); 

        glBegin(GL_QUADS); //Face de trás 
            glNormal3f(0.0, 0.0, 1.0); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, 0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, 0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( obj->getSizex()/100.0, obj->getSizey()/100.0 ); 
            glVertex3i(obj->getPosx()+obj->getSizex(), obj->getPosy()+obj->getSizey(), obj->getPosz()+obj->getSizez()); 
            if (obj->getTextureType() == TEX_2D) glTexCoord2f( 0, obj->getSizey()/100.0 ); 
            glVertex3i(obj->getPosx(), obj->getPosy()+obj->getSizey(), obj->getPosz()+obj->getSizez()); 
        glEnd(); 

        if (obj->getTextureType() == TEX_2D) glDisable(GL_TEXTURE_2D); 
        else if (obj->getTextureType() == REFLECT) { 

           //Not working properly yet 
        } 

} 
 
void Screen::updateScreen(Map *actual, Actor *hero){ 

    glMatrixMode(GL_MODELVIEW); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

    vector<MapElement *> first; 
    vector<MapElement *> second; 
    vector<MapElement *> third; 
    vector<MapElement *> fourth; 
    vector<MapElement *> all; 

    //Primeiro colocam-se os objetos estáticos. 
    for (unsigned int i = 0; i < actual->getWallsNum(); i++){ 

        //Primeiro checa a interseção 
        if (actual->getWall(i)->getAlwaysDraw()) all.push_back(actual->getWall(i)); 
        //Melhorar isso aqui para as 4 direções. 
        else { 

            if (actual->getWall(i)->getPosx() >= hero->getPosx()){ 

                if (actual->getWall(i)->getPosz() >= hero->getPosz()) first.push_back(actual->getWall(i)); 
                else third.push_back(actual->getWall(i)); 

            } else { 

                if (actual->getWall(i)->getPosz() >= hero->getPosz()) second.push_back(actual->getWall(i)); 
                else fourth.push_back(actual->getWall(i)); 

            } 

        } 

    } 

    //Agora os objetos dinâmicos. 
    //all.push_back(hero); 
    for (unsigned int i = 1; i < actual->getActorsNum(); i++){ 


        if (actual->getActor(i)->getPosx() >= hero->getPosx()){ 

             if (actual->getActor(i)->getPosz() >= hero->getPosz()) first.push_back(actual->getActor(i)); 
             else third.push_back(actual->getActor(i)); 

        } else { 

             if (actual->getActor(i)->getPosz() >= hero->getPosz()) second.push_back(actual->getActor(i)); 
             else fourth.push_back(actual->getActor(i)); 

        } 


    } 

    //Projeteis 
    for (unsigned int i = 0; i < actual->getProjectilesNum(); i++){ 
 
        if (actual->getProjectile(i)->getPosx() >= hero->getPosx()){ 

             if (actual->getProjectile(i)->getPosz() >= hero->getPosz()) first.push_back(actual->getProjectile(i)); 
             else third.push_back(actual->getProjectile(i)); 

        } else { 

             if (actual->getProjectile(i)->getPosz() >= hero->getPosz()) second.push_back(actual->getProjectile(i)); 
             else fourth.push_back(actual->getProjectile(i)); 

        } 


    } 

    //Depois dos cálculos desenha os objetos. Primeiros os que sempre vão. 
    for (int j = 0; j < all.size(); j++) { 

        if (all[j]->hasMaterial()) applyMaterial(all[j]->getMaterial()); 

        else applyNullMaterial(); 

        drawStaticObject(all[j]); 

    } 

    //Desenha ator. Por enquanto sem animaçoes. 

    if (actualCamera > 0) { 

        drawDinamicObject(actual->getActor(0)); 
        //Por enquanto sem filtro. Mas ser´a instituido. 
        for (int j = 0; j < first.size(); j++) drawObject(first[j]); 
        for (int j = 0; j < second.size(); j++) drawObject(second[j]); 
        for (int j = 0; j < third.size(); j++) drawObject(third[j]); 
        for (int j = 0; j < fourth.size(); j++) drawObject(fourth[j]); 

    } else { 

        //Dependendo da direção, ele desenha os objetos. 
        if (hero->getDirection() > 27 || hero->getDirection() < 13) for (int j = 0; j < first.size(); j++) drawObject(first[j]); 
        if (hero->getDirection() > 21 || hero->getDirection() < 5) for (int j = 0; j < second.size(); j++) drawObject(second[j]); 
        if (hero->getDirection() > 5 && hero->getDirection() < 21) for (int j = 0; j < third.size(); j++) drawObject(third[j]); 
        if (hero->getDirection() > 11 && hero->getDirection() < 29) for (int j = 0; j < fourth.size(); j++) drawObject(fourth[j]); 

    } 

    glLoadIdentity(); 

    if (actualCamera == 0) gluLookAt( 
            hero->getPosx(), (hero->getSizey() + hero->getPosy()) * 0.95, hero->getPosz(), 
            hero->getPosx() + dirX[0][hero->getDirection()], 
            (hero->getSizey() + hero->getPosy())*0.95 + hero->getAim(), 
            hero->getPosz() + dirZ[0][hero->getDirection()], 
            0, 1,0 
        ); 
    else { 

        int dist = cams[actualCamera]->getDistance(); 
        int height = cams[actualCamera]->getHeight(); 
        int dir = cams[actualCamera]->getDirection(); 

        int direct = dir + hero->getDirection(); 

        if (direct > 31) direct -= 32; 

        gluLookAt( hero->getPosx()+(dist*dirX[1][direct]), hero->getPosy()+height, hero->getPosz()+(dist*dirZ[1][direct]), hero->getPosx(), (hero->getSizey() + hero->getPosy()) * 0.95, hero->getPosz(),0,1,0); 
    } 

    SDL_GL_SwapBuffers(); 

} 

void Screen::applyMaterial(Material *mat){ 

    float nada[4] = {0, 0, 0, 0}; 
    if (mat->hasDiffuse) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat->diffuse); 
    else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, nada); 
    if (mat->hasSpecular) glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat->specular ); 
    else glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, nada ); 
    if (mat->hasEmission) glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat->emission); 
    else glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nada); 
    if (mat->hasAmbient) glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat->ambient); 
    else glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat->shineness); 

} 

void Screen::applyNullMaterial(){ 

    float nada[4] = {0, 0, 0, 0}; 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, nada); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, nada ); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nada); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0); 

} 

void Screen::drawObject(MapElement *obj){ 

     if (obj->getDinamic()) drawDinamicObject(obj); 
     else drawStaticObject(obj); 

} 

void Screen::drawDinamicObject(MapElement *obj){ 
 
    unsigned int actualMat = 3000; 

    if (obj->getIsNPC()) { 

        Actor *temp = (Actor*) obj; 

        glPushMatrix(); 
        if (obj->getDirection() > 0) { 
            glTranslatef(obj->getPosx(), obj->getPosy(), obj->getPosz()); 
            glRotatef(11.25*obj->getDirection(), 0, 1, 0); 
            glTranslatef(-obj->getPosx(), -obj->getPosy(), -obj->getPosz()); 

        } 


        for (unsigned int i = 0; i < temp->getModel()->getAllTriangles()->size(); i++){ 

            Vertex v1, v2, v3; 

            v1 = temp->getModel()->getAllTriangles()->at(i)->points[0]; 
            v2 = temp->getModel()->getAllTriangles()->at(i)->points[1]; 
            v3 = temp->getModel()->getAllTriangles()->at(i)->points[2]; 

            if (obj->hasMaterial() && temp->getModel()->getAllTriangles()->at(i)->matIndex != actualMat) { 

                applyMaterial(temp->getMaterial(temp->getModel()->getAllTriangles()->at(i)->matIndex)); 
                actualMat = temp->getModel()->getAllTriangles()->at(i)->matIndex; 
            } 

            glBegin(GL_TRIANGLES); 

            glNormal3f(v1.nX, v1.nY, v1.nZ); 
            glVertex3f(v1.x+obj->getPosx(), v1.y+obj->getPosy(), v1.z+obj->getPosz()); 

            glNormal3f(v2.nX, v2.nY, v2.nZ); 
            glVertex3f(v2.x+obj->getPosx(), v2.y+obj->getPosy(), v2.z+obj->getPosz()); 

            glNormal3f(v3.nX, v3.nY, v3.nZ); 
            glVertex3f(v3.x+obj->getPosx(), v3.y+obj->getPosy(), v3.z+obj->getPosz()); 

            glEnd(); 

        } 

        glPopMatrix(); 

    } else { 

        Projectile *temp = (Projectile *) obj; 

        glPushMatrix(); 
        if (obj->getDirection() > 0) { 
            glTranslatef(obj->getPosx(), obj->getPosy(), obj->getPosz()); 
            glRotatef(11.25*obj->getDirection(), 0, 1, 0); 
            glTranslatef(-obj->getPosx(), -obj->getPosy(), -obj->getPosz()); 

        } 
 
        for (unsigned int i = 0; i < temp->getModel()->getAllTriangles()->size(); i++){ 

            Vertex v1, v2, v3; 

            v1 = temp->getModel()->getAllTriangles()->at(i)->points[0]; 
            v2 = temp->getModel()->getAllTriangles()->at(i)->points[1]; 
            v3 = temp->getModel()->getAllTriangles()->at(i)->points[2]; 

            if (obj->hasMaterial() && temp->getModel()->getAllTriangles()->at(i)->matIndex != actualMat) { 

                applyMaterial(temp->getMaterial(temp->getModel()->getAllTriangles()->at(i)->matIndex)); 
                actualMat = temp->getModel()->getAllTriangles()->at(i)->matIndex; 
            } 

            glBegin(GL_TRIANGLES); 

            glNormal3f(v1.nX, v1.nY, v1.nZ); 
            glVertex3f(v1.x+obj->getPosx(), v1.y+obj->getPosy(), v1.z+obj->getPosz()); 

            glNormal3f(v2.nX, v2.nY, v2.nZ); 
            glVertex3f(v2.x+obj->getPosx(), v2.y+obj->getPosy(), v2.z+obj->getPosz()); 

            glNormal3f(v3.nX, v3.nY, v3.nZ); 
            glVertex3f(v3.x+obj->getPosx(), v3.y+obj->getPosy(), v3.z+obj->getPosz()); 

            glEnd(); 

        } 

        glPopMatrix(); 
    } 

} 

void Screen::setCamera(unsigned int num){ 

    if (num < cams.size()) actualCamera = num; 

} 

Texture2D *Screen::load2DTextureFromFile(char *path){ 

        Texture2D *image = new Texture2D; 
        bool standard = false; 

        SDL_Surface *imageRAW = IMG_Load(path); 

        //Trata o erro de leitura... 
        if(!imageRAW) { 
           standard = true; 
        } 

        glGenTextures(1, &image->id); 
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        glBindTexture(GL_TEXTURE_2D, image->id); 

        if (!standard) gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageRAW->w, imageRAW->h, GL_RGB, GL_UNSIGNED_BYTE, imageRAW->pixels); 
                else { 
                    float pixels[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f}; 
                    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 3, 3, GL_RGB, GL_FLOAT, pixels); 
                } 

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); 
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST); 


        SDL_FreeSurface(imageRAW); 
        return image; 
} 


int Screen::add2DTexture(char *path){ 

    Texture2D *tex1 = load2DTextureFromFile(path); 
    return tex1->id; 

} 

SDL_Surface * Screen::getMainSurface(){ 
    return main; 
} 

unsigned int Screen::getActualCameraIndex(){ 
    return actualCamera; 
} 

Camera * Screen::getCamera(int i){ 
    return cams[i]; 
} 

void Screen::setFullScreen(){ 

    if (!fullScreen){ 

        main = SDL_SetVideoMode(width, height, depth, SDL_OPENGL | SDL_FULLSCREEN); 
        fullScreen = true; 

    } else { 

        main = SDL_SetVideoMode(width, height, depth, SDL_OPENGL); 
        fullScreen = false; 
    } 
} 

void Screen::setAmbientColor(Vertex col){ 

    light_ambient[0] = col.x; 
    light_ambient[1] = col.y; 
    light_ambient[2] = col.z; 
    light_ambient[3] = 0; 

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
 
} 

void Screen::enableFog(float start, float end){ 

    glEnable(GL_FOG); 

    //Standard configurations... 
    glFogi(GL_FOG_MODE, GL_LINEAR); 
    glFogf(GL_FOG_START, start); 
    glFogf(GL_FOG_END, end); 

    glFogfv(GL_FOG_COLOR, light_ambient); 
    glFogf(GL_FOG_DENSITY, 0.5); 
    glFogi(GL_FOG_HINT, GL_FASTEST); 

} 

void Screen::disableFog(){ 

    glDisable(GL_FOG); 

} 

void Screen::setFogParameters(float *color, float dens, bool hitBetter, float start, float end){ 

    if (hitBetter) glFogi(GL_FOG_HINT, GL_NICEST); 
    else glFogi(GL_FOG_HINT, GL_FASTEST); 
    glFogfv(GL_FOG_COLOR, color); 
    glFogf(GL_FOG_DENSITY, dens); 
    glFogf(GL_FOG_START, start); 
    glFogf(GL_FOG_END, end); 

} 

void Screen::addCamera(Camera *cam){ 

    cams.push_back(cam); 

}
