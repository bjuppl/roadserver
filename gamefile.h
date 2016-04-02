#ifndef GAMEFILE_H
#define GAMEFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "gamemodel.h"

class Game;

class GameFileManager {

    Game *game;
public:
    GameFileManager( Game *game_ ,std::vector<std::string> contents );
    static GameFileManager *fromFile( Game *game_, std::string fileName );

    std::string toGameFile();

};


#endif // GAMEFILE_H
