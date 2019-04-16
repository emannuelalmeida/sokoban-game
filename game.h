#ifndef GAME_H 
#define GAME_H 
#include "fisica.h" 
#include "screen.h" 
#include "configuration.h" 
#include <stdlib.h> 


enum GameState {MENU, GAME, ASK_ANSWER, INTERLUDE}; 

class Game 
{ 
public: 
    Game(); 
    ~Game(); 

    //Essa função será específica de cada jogo, representa o método de funcionamento da engine. 
    void newGame(); 
    void resetGame(); 
    void quitGame(); 

    GameState getState(); 
    Actor * getHero(); 
    Map * getActualMap(); 

    void setHero(Actor *); 
    void setActualMap(Map *); 
    void setState(GameState); 

private: 
    void actorsThinkAct(); 
    void checkAndMoveObjects(); 
    void getInputEvents(); 
    void readPressedKey(SDL_keysym *keysym); 
    void doJumpGravity(); 
    void populateMaterials(); 
    void startMainLoop(); 

    //Funções de controle, devem ser divididas por estado de jogo 
    GameState state; 

    //Um ator será relacionado ao jogo, como ator principal, se não houver jogo é apenas um ponteiro... 
    Actor *hero; 
    //Um mapa foi adicionado como principal, por onde o jogo acontece pelo menos nesse momento. 
    Map *actual; 
    Screen sc; 
    bool newMap; 

    //E uma ideia interessante para demonstrar o codigo mas provavelmente ficara. 
    vector<Material *> matBank; 

}; 

#endif // GAME_H
