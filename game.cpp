#include "game.h" 

void Game::populateMaterials(){ 

    Material *emerald = new Material(); 
    emerald->hasDiffuse = true; 
    emerald->hasSpecular = true; 
    emerald->hasAmbient = true; 

    float emeDif[4] = {0.07568, 0.61424, 0.07568, 0}; 
    float specDif[4] = {0.633, 0.727811, 0.633, 0}; 
    float ambDif[4] = {0.0215, 0.1745, 0.0215, 0}; 

    emerald->shineness = 0.6; 
    memcpy(emerald->diffuse, emeDif, 4 * sizeof(float)); 
    memcpy(emerald->specular, specDif, 4 * sizeof(float)); 
    memcpy(emerald->ambient, ambDif, 4 * sizeof(float)); 

    matBank.push_back(emerald); 

    Material *gold = new Material(); 
    gold->hasDiffuse = true; 
    gold->hasSpecular = true; 
    gold->hasAmbient = true; 

    float emeDif1[4] = {0.75164, 0.60648, 0.22648, 0}; 
    float specDif1[4] = {0.628281, 0.555802, 0.366065, 0}; 
    float ambDif1[4] = {0.24725, 0.1995, 0.0745, 0}; 

    gold->shineness = 0.4; 
    memcpy(gold->diffuse, emeDif1, 4 * sizeof(float)); 
    memcpy(gold->specular, specDif1, 4 * sizeof(float)); 
    memcpy(gold->ambient, ambDif1, 4 * sizeof(float)); 

    matBank.push_back(gold); 

    Material *ruby = new Material(); 
    ruby->hasDiffuse = true; 
    ruby->hasSpecular = true; 
    ruby->hasAmbient = true; 

    float emeDif2[4] = {0.61424, 0.04136, 0.04136, 0}; 
    float specDif2[4] = {0.727811, 0.626959, 0.626959, 0}; 
    float ambDif2[4] = {0.1745, 0.01175, 0.01175, 0}; 

    ruby->shineness = 0.6; 
    memcpy(ruby->diffuse, emeDif2, 4 * sizeof(float)); 
    memcpy(ruby->specular, specDif2, 4 * sizeof(float)); 
    memcpy(ruby->ambient, ambDif2, 4 * sizeof(float)); 

    matBank.push_back(ruby); 

    Material *silver = new Material(); 
    silver->hasDiffuse = true; 
    silver->hasSpecular = true; 
    silver->hasAmbient = true; 

    float emeDif3[4] = {0.50754, 0.50754, 0.50754, 0}; 
    float specDif3[4] = {0.508273, 0.508273, 0.508273, 0}; 
    float ambDif3[4] = {0.19225, 0.19225, 0.19225, 0}; 

    silver->shineness = 0.4; 
    memcpy(silver->diffuse, emeDif3, 4 * sizeof(float)); 
    memcpy(silver->specular, specDif3, 4 * sizeof(float)); 
    memcpy(silver->ambient, ambDif3, 4 * sizeof(float)); 

    matBank.push_back(silver); 

    Material *brass = new Material(); 
    brass->hasDiffuse = true; 
    brass->hasSpecular = true; 
    brass->hasAmbient = true; 

    float emeDif4[4] = {0.780392, 0.568627, 0.113725, 0}; 
    float specDif4[4] = {0.992157, 0.941176, 0.807843, 0}; 
    float ambDif4[4] = {0.329412, 0.223529, 0.027451, 0}; 

    brass->shineness = 0.6; 
    memcpy(brass->diffuse, emeDif4, 4 * sizeof(float)); 
    memcpy(brass->specular, specDif4, 4 * sizeof(float)); 
    memcpy(brass->ambient, ambDif4, 4 * sizeof(float)); 

    matBank.push_back(brass); 


} 

Game::Game() 
{ 

    //Todos os códigos de início do jogo deverão estar presentes aqui. 
    state = MENU; 

    //Etapa onde as últimas configurações são adquiridas 
    //--CÓDIGO DE TESTE-- 
    Configuration conf = Configuration(); 
    //--CÓDIGO DE TESTE-- 

    populateMaterials(); 

    sc = Screen(); 
    sc.setParameters(conf.compTela, conf.largTela, conf.profundCor); 

    //Inicia o sistema da SDL com seus subsistemas. 
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTTHREAD)==-1)) { 
            printf("Could not initialize SDL: %s.\n", SDL_GetError()); 
            exit(-1); 
        } 
    SDL_EnableKeyRepeat(60, 60); 


    //Toda a parte gráfica de início da tela. 
    sc.startScreen(); 

    newMap = false; 

    //Nenhum erro até agora e terminadas as preparações, entrega o jogo ao seu loop principal 
    startMainLoop(); 


} 

Game::~Game(){ 
    //destrutor 
} 

void Game::startMainLoop(){ 

    while (1){ 

    switch(state){ 

        case MENU: { 

            newGame(); 

            break; 

        } 

        case GAME: { 

            //Iniciar procedimentos padrões em cada passo do jogo. 
            //Iniciando o pensamento e decisão de todos os atores do jogo. 

            if (newMap) { 
                sc.setAmbientColor(actual->getAmbColor()); 
                newMap = false; 

                sc.enableFog(0, 600); 
                float color[] = {0.3, 0.5, 0.3, 0.0}; 

                sc.setFogParameters(color, 0.8, true, 0, 600); 
            } 

            actorsThinkAct(); 
            //Move os projéteis, se houverem. 
            checkAndMoveObjects(); 
            //Função que realiza os movimentos pra baixo de quem não estiver voando. 
            doJumpGravity(); 
            //Detecta qualquer evento do teclado, mouse ou joystick passado pelo jogador. 
            getInputEvents(); 
            //Desenha tudo na tela de acordo como tem que ser. 
            sc.updateScreen(actual, hero); 

            break; 
        } 

        case ASK_ANSWER: { 


            break; 
        } 

        case INTERLUDE : { 

            break; 
        } 

        SDL_Delay(30); 

    } 

    } 

} 

//Independente dos parâmetros selecionados o jogo inicia aqui. 
void Game::newGame(){ 

    //--Código de teste-- 
    //Personagem principal 
    hero = new Actor(0, 15, 21, 15, 10, 25, 10, 0); 
    hero->setModel(new Model("stuff/pessoa.x")); 
    actual = new Map("teste"); 
    actual->putActor(hero); 

    //Cor da luz ambiente. 
    Vertex clAmb; 
    clAmb.x = 0.5; 
    clAmb.y = 0.5; 
    clAmb.z = 0.5; 

    actual->setAmbColor(clAmb); 

    //Paredes, chao e tetos. 
    Wall *ground1 = new Wall(0, 10, 10, 10, 200, 10, 200); 
    ground1->setAlwaysDraw(true); 
    ground1->setTextureType(TEX_2D); 
    int roomTex = sc.add2DTexture("stuff/brick-floor.jpg"); 
    ground1->setTextIndex(roomTex); 

    Wall *ground2 = new Wall(1, 210, 10, 100, 250, 13, 50); 
    ground2->setAlwaysDraw(true); 
    ground2->setMaterial(matBank[3]); 
    ground2->setTextureType(TEX_2D); 
    int corridTex = sc.add2DTexture("stuff/mesh-texture.jpg"); 
    ground2->setTextIndex(corridTex); 

    Wall *ground3 = new Wall(2, 412, 10, 150, 50, 13, 251); 
    ground3->setAlwaysDraw(true); 
    ground3->setMaterial(matBank[3]); 
    ground3->setTextureType(TEX_2D); 
    ground3->setTextIndex(corridTex); 

    Wall *ground4 = new Wall(3, 312, 10, 402, 200, 10, 200); 
    ground4->setAlwaysDraw(true); 
    ground4->setTextureType(TEX_2D); 
    ground4->setTextIndex(roomTex); 

    Wall *ceilling1 = new Wall(5, 10, 70, 10, 200, 10, 200); 
    ceilling1->setAlwaysDraw(true); 
    ceilling1->setTextureType(TEX_2D); 
    ceilling1->setTextIndex(roomTex); 

    Wall *ceilling2 = new Wall(6, 211, 73, 100, 250, 13, 50); 
    ceilling2->setAlwaysDraw(true); 
    ceilling2->setMaterial(matBank[3]); 
    ceilling2->setTextureType(TEX_2D); 
    ceilling2->setTextIndex(corridTex); 

    Wall *ceilling3 = new Wall(7, 412, 73, 151, 50, 13, 250); 
    ceilling3->setAlwaysDraw(true); 
    ceilling3->setMaterial(matBank[3]); 
    ceilling3->setTextureType(TEX_2D); 
    ceilling3->setTextIndex(corridTex); 

    Wall *ceilling4 = new Wall(8, 312, 70, 402, 200, 10, 200); 
    ceilling4->setAlwaysDraw(true); 
    ceilling4->setTextureType(TEX_2D); 
    ceilling4->setTextIndex(roomTex); 

    Wall *Wall1 = new Wall(9, 2, 10, 10, 8, 60, 200); 
    Wall1->setAlwaysDraw(true); 
    int WallTex = sc.add2DTexture("stuff/textura-mosaico-1.jpg"); 
    Wall1->setTextureType(TEX_2D); 
    Wall1->setTextIndex(WallTex); 

    Wall *Wall2 = new Wall(10, 10, 10, 2, 200, 60, 8); 
    Wall2->setAlwaysDraw(true); 
    Wall2->setTextureType(TEX_2D); 
    Wall2->setTextIndex(WallTex); 

    Wall *Wall3 = new Wall(11, 10, 10, 210, 200, 60, 8); 
    Wall3->setAlwaysDraw(true); 
    Wall3->setTextureType(TEX_2D); 
    Wall3->setTextIndex(WallTex); 

    Wall *Wall4 = new Wall(12, 210, 10, 10, 8, 60, 90); 
    Wall4->setAlwaysDraw(true); 
    Wall4->setTextureType(TEX_2D); 
    Wall4->setTextIndex(WallTex); 

    Wall *Wall5 = new Wall(13, 210, 10, 150, 8, 60, 60); 
    Wall5->setAlwaysDraw(true); 
    Wall5->setTextureType(TEX_2D); 
    Wall5->setTextIndex(WallTex); 

    Wall *Wallcoor1 = new Wall(14, 208, 13, 92, 252, 60, 8); 
    Wallcoor1->setAlwaysDraw(true); 
    Wallcoor1->setTextureType(TEX_2D); 
    Wallcoor1->setTextIndex(WallTex); 

    Wall *Wallcoor2 = new Wall(15, 208, 13, 150, 204, 60, 8); 
    Wallcoor2->setAlwaysDraw(true); 
    Wallcoor2->setTextureType(TEX_2D); 
    Wallcoor2->setTextIndex(WallTex); 

    Wall *Wallcoor3 = new Wall(16, 404, 13, 150, 8, 60, 252); 
    Wallcoor3->setAlwaysDraw(true); 
    Wallcoor3->setTextureType(TEX_2D); 
    Wallcoor3->setTextIndex(WallTex); 

    Wall *Wallcoor4 = new Wall(17, 460, 13, 100, 8, 60, 302); 
    Wallcoor4->setAlwaysDraw(true); 
    Wallcoor4->setTextureType(TEX_2D); 
    Wallcoor4->setTextIndex(WallTex); 

    Wall *Wall6 = new Wall(18, 312, 10, 394, 100, 60, 8); 
    Wall6->setAlwaysDraw(true); 
    Wall6->setTextureType(TEX_2D); 
    Wall6->setTextIndex(WallTex); 

    Wall *Wall7 = new Wall(19, 462, 10, 394, 50, 60, 8); 
    Wall7->setAlwaysDraw(true); 
    Wall7->setTextureType(TEX_2D); 
    Wall7->setTextIndex(WallTex); 

    Wall *Wall8 = new Wall(20, 312, 10, 602, 200, 60, 8 ); 
    Wall8->setAlwaysDraw(true); 
    Wall8->setTextureType(TEX_2D); 
    Wall8->setTextIndex(WallTex); 

    Wall *Wall9 = new Wall(21, 304, 10, 402, 8, 60, 200 ); 
    Wall9->setAlwaysDraw(true); 
    Wall9->setTextureType(TEX_2D); 
    Wall9->setTextIndex(WallTex); 

    Wall *Wall10 = new Wall(22, 504, 10, 402, 8, 60, 200 ); 
    Wall10->setAlwaysDraw(true); 
    Wall10->setTextureType(TEX_2D); 
    Wall10->setTextIndex(WallTex); 

    actual->putWall(ground1); 
    actual->putWall(ground2); 
    actual->putWall(ground3); 
    actual->putWall(ground4); 
    actual->putWall(ceilling1); 
    actual->putWall(ceilling2); 
    actual->putWall(ceilling3); 
    actual->putWall(ceilling4); 
    actual->putWall(Wall1); 
    actual->putWall(Wall2); 
    actual->putWall(Wall3); 
    actual->putWall(Wall4); 
    actual->putWall(Wall5); 
    actual->putWall(Wallcoor1); 
    actual->putWall(Wallcoor2); 
    actual->putWall(Wallcoor3); 
    actual->putWall(Wallcoor4); 
    actual->putWall(Wall6); 
    actual->putWall(Wall7); 
    actual->putWall(Wall8); 
    actual->putWall(Wall9); 
    actual->putWall(Wall10); 

    //Bonecos que irao se mover de acordo com o comportamento acertado. 
    Actor *boneco1 = new Actor(1, 482, 21, 432, 0, 0, 0, 24); 
    boneco1->setModel(new Model("stuff/pessoa.x")); 

    Actor *boneco2 = new Actor(2, 342, 21, 432, 0, 0, 0, 0); 
    boneco2->setModel(new Model("stuff/pessoa.x")); 

    Actor *boneco3 = new Actor(3, 342, 21, 572, 0, 0, 0, 8); 
    boneco3->setModel(new Model("stuff/pessoa.x")); 

    Actor *boneco4 = new Actor(4, 482, 21, 572, 0, 0, 0, 16); 
    boneco4->setModel(new Model("stuff/pessoa.x")); 

    actual->putActor(boneco1); 
    actual->putActor(boneco2); 
    actual->putActor(boneco3); 
    actual->putActor(boneco4); 

    Camera *cam1  = new Camera(1, 50, 15, 0); 
    sc.addCamera(cam1); 

    newMap = true; 

    //--Código de teste-- 

    state = GAME; 


} 

void Game::resetGame(){ 
    //TODO 
} 

void Game::quitGame(){ 

    SDL_Quit(); 
    exit(0); 
} 

void Game::actorsThinkAct(){ 

    //Por convenção o primeiro ator é o herói, então esse processo inicia-se da posição 1 do vetor de atores. 
    for (unsigned int i = 1; i < actual->getActorsNum();i++){ 


        move(actual, actual->getActor(i), 0); 
        if (actual->getActor(i)->getPosx() >= 482 && actual->getActor(i)->getPosz() <= 432 || 
                actual->getActor(i)->getPosx() <= 342 && actual->getActor(i)->getPosz() <= 432 || 
                actual->getActor(i)->getPosx() <= 342 && actual->getActor(i)->getPosz() >= 572 || 
                actual->getActor(i)->getPosx() >= 482 && actual->getActor(i)->getPosz() >= 572) actual->getActor(i)->sumDirection(8); 

    } 

} 

void Game::checkAndMoveObjects(){ 

    for (unsigned int i = 0; i < actual->getProjectilesNum(); i++){ 

        CollisionResult place = move(actual, actual->getProjectile(i), 0); 

        if (place.hit && place.where != hero){ 

            if (place.where->getDinamic() && place.where->getIsNPC()){ 


                int x = place.where->getMaterialIndex(); 
                if (x < 4) { 

                    //printf("Bateu!!\n"); 
                    Actor *temp = (Actor *) place.where; 
                    temp->setMaterialWithIndex(matBank[x+1], 0); 
                    temp->setMaterialIndex(x+1); 

                } 
            } 

            actual->getProjectile(i)->setDestroyed(); 
            //realiza ação de cálculo de dano ou coisa parecida. 
        } 
    } 

    //Deletar os que foram marcados como destruídos. 
    unsigned int i =0; 
    while (i < actual->getProjectilesNum()){ 
        if (actual->getProjectile(i)->isDestroyed()) { 

            actual->deleteProjectile(i); 

        } else i++; 
    } 

} 

void Game::getInputEvents(){ 

    SDL_Event event; 

        //Função genérica que processa qualquer tipo de evento pelo SDL 
        while( SDL_PollEvent( &event ) ) { 
            switch( event.type ) { 
            //Processa o pressionamento de uma tecla 
            case SDL_KEYDOWN: 
                readPressedKey( &event.key.keysym ); 
                break; 

            //Processa a liberação de uma tecla... Às vezes é útil, vamos ver... 
            case SDL_KEYUP:{ 

                break; 
            } 

            case SDL_QUIT:{ 

                quitGame(); 
                break; 
            } 
            } 

    } 

} 

void Game::readPressedKey(SDL_keysym* keysym){ 


    //O processamento de eventos depende de que estado do jogo está ativo no momento. 
    switch(state){ 

        case MENU: { 

            break; 

        } 

        case GAME: { 

        switch( keysym->sym ) { 
            case SDLK_ESCAPE: 
                quitGame(); 
                break; 
            case SDLK_SPACE: 
                if (!hero->getFalling() && hero->getJumpRest() == 0) hero->setJumpRest(15); 
                break; 
            case SDLK_q: 
                hero->setAim(1); 
                break; 

            case SDLK_x: 
                hero->setAim(-1); 
                break; 

            case SDLK_UP: 
                move(actual, hero, 0); 

                break; 

            case SDLK_DOWN: 
                move(actual, hero, 1); 
                break; 

            case SDLK_LEFT: 
                hero->sumDirection(1); 
                break; 
            case SDLK_RIGHT: 
                hero->sumDirection(-1); 
                break; 
            case SDLK_a: 
                move(actual, hero, 2); 
                break; 

            case SDLK_s: 
                move(actual, hero, 3); 
                break; 
            case SDLK_f: 
                sc.setFullScreen(); 
                break; 
            case SDLK_c: 
                sc.setCamera(1); 
                break; 
            case SDLK_z: 
                actual->putProjectile(new Projectile(1, true, 1, hero->getPosx(), hero->getPosy(), hero->getPosz(), hero->getDirection(), hero->getAim(), new Model("stuff/bola.x"))); 
                break; 
            default: 
                break; 
        } 
        } 

        case ASK_ANSWER: { 


            break; 
        } 

        case INTERLUDE : { 

            break; 
        } 

    } 


} 

GameState Game::getState(){ 
    return state; 
} 

Actor * Game::getHero(){ 
    return hero; 
} 

Map * Game::getActualMap(){ 
    return actual; 
} 

void Game::setHero(Actor *_hero){ 
    hero = _hero; 
} 
 
void Game::setActualMap(Map *_actual){ 
    actual = _actual; 
} 

void Game::setState(GameState st){ 
    state = st; 
} 

void Game::doJumpGravity(){ 

    for (unsigned int i = 0; i < actual->getActorsNum(); i++){ 

        if (actual->getActor(i)->getJumpRest() > 0){ 
            jumpUp(actual, actual->getActor(i)); 
            continue; 
        } 

        if (actual->getActor(i)->isGravityAffected()) continue; 

        //Se não estiver pulando e nem voando ele começa a cair. 
        if (fallDown(actual, actual->getActor(i))){ 
            actual->getActor(i)->setFalling(true); 
        } else actual->getActor(i)->setFalling(false); 

    } 

} 
