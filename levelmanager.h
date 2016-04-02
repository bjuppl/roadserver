#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QFile>
#include <QResource>
#include <QTextStream>
#include <QIODevice>

#include <iostream>
#include <string>
#include <vector>

//#include "gui.h"
#include "gamemodel.h"
#include "utils.h"

using namespace std;

class Game;

struct difficultyStruct{
//mods change based on various difficulties
    int woodMod;
    int goldMod;
    int waterMod;
    int stoneMod;
    difficultyStruct(int wm, int gm, int wam, int stm){

        woodMod = wm;
        goldMod = gm;
        waterMod = wam;
        stoneMod = stm;

      }
    difficultyStruct(){}
};
class LevelManager {

private:
    int curLevel{0};
    //static LevelManager *instance_;
    Game *game;
    difficultyStruct *duff{new difficultyStruct()};

    //enable random events
    bool randEn = true;
 public:
    //static LevelManager& instance();
    LevelManager(Game *game_) : game(game_) {}
    vector<QString> levelMaker(QString gamedata);
    ~LevelManager() { delete duff;}
    void increaseLevel();
    std::vector<std::string> getLevel( std::string name );
    std::vector<std::string> getLevel( int num );

    std::vector<std::string> resourceFileContents( std::string alias );
    difficultyStruct *getDuff(){return duff;}
    bool getRand(){return randEn;}
    void setRand(bool rand){randEn = rand;}
    string upRec(int goodRes);
    string downRec(int badRes);
    bool killStruct(int hit,int wid);
    bool riverSquare(int hit,int wid);
    bool burnSquare(int hit, int wid);
    bool quakeSquare(int hit, int wid);
};



#endif // LEVELMANAGER_H
