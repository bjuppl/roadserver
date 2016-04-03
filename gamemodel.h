#ifndef GAMEMODEL_
#define GAMEMODEL_

#include <string>
#include <vector>

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include "square.h"
#include "gamefile.h"
#include "updater.h"
#include "levelmanager.h"
#include "player.h"

#include "utils.h"
//#include "gui.h"

using namespace std;

//class GuiManager;
class Square;
class Updater;
class Player;
class GameFileManager;
class LevelManager;

// This is a way to keep track of information and rules about specific resources.
struct Resource {
    std::string name, shortName;
    Game *game;
    int value;
    Resource(Game *game_, string name_, string shortName_, int value_): game(game_), name(name_), shortName(shortName_), value(value_) {}
};

struct Price {
    std::string type;
    int amount;
    Game *game;
    Price( Game *game_, std::string t, int a) : game(game_), type(t), amount(a) {}
};

struct Structure {
    std::string name, shortName;
    Game *game;
    vector<Price> cost;
    Structure(Game *game_, std::string name_, std::string shortName_, vector<Price> cost_): game(game_), name(name_), shortName(shortName_), cost(cost_) {}
};



//the actual game model
class Game{

  private:

    bool isLocalGame {false};
    vector<vector<Square*>> squares;
    vector<Resource*> resource_types;
    vector<Structure*> structure_types;
    bool isActive { false};
    //for singleton if needed
    GameFileManager *loader;
    Updater *updater;
    string id;
    string alias;
    string password;
    int round_num;
    vector<Player*> player_list;
    Player *curPlayer;
    int width, height;
    string diff;
    vector<QString> serverinfo;
  public:
    LevelManager *level_manager;
    bool applyCommand( std::string command );
    bool save();
    string load();
    void update();

    //moar singleton functionality
    string getDiff(){return diff;}
    void setDiff(string newdiff);

    bool getIsActive() { return isActive; }
    bool setIsActive() { return isActive; }
private:
    //static Game* instance_;

public:
    Game ( string id_ );
    //static Game& instance();
    void setGameLoader ( GameFileManager * gfm );
    void start();

    ~Game();
    GameFileManager *getGameLoader () { return loader; }

    void updateResources();

    void purchaseAddition( Square* source );

    int expectedPlayerNum();
    string gameFilePlayerList();
    string gameFileResourceList();

    //getters n setters

    vector<Structure*> getStructures() { return structure_types; }
    Structure *getStructure ( string shortName );
    vector<Resource*> getResources() { return resource_types; }
    Resource *getResource ( string shortName );
    vector<vector<Square*>> getSquares() { return squares; }
    Square *getSquare ( int x, int y) { return squares[x][y]; }
    Square *getSquare ( int id );
    vector<Square*> getPlayerSquares ( Player *owner );
    string getId() { return id; }
    string getAlias() { return alias; }
    string getPassword() { return password; }
    int getRoundNum() { return round_num; }
    vector<Player*> getPlayerList() { return player_list; }
    Player *getPlayer ( std::string name);
    int getWidth() { return width; }
    int getHeight() { return height; }
    bool getIsLocalGame() { return isLocalGame; }
    Player *getCurPlayer(  ) { return curPlayer; }
    Updater *getUpdater() { return updater; }
    LevelManager *getLevelManager(){ return level_manager; }

    void setLevelManager( LevelManager* lm ) { level_manager = lm; }
    void setUpdater( Updater *u) { updater = u; }
    void setCurPlayer( Player* c ) { curPlayer = c; }
    void setIsLocalGame( bool tf) { isLocalGame = tf; }
    void setStructures ( vector<Structure*> sl );
    void addStructure ( Structure * s ) { structure_types.push_back(s); }
    void setResources ( vector<Resource*> vr );
    void addResource ( Resource * r ) { resource_types.push_back(r); }
    void setSquares ( vector<vector<Square*>> sq );
    void setSquare ( Square * sq, int x, int y ) { delete squares[x][y]; squares[x][y] = sq; }
    void setId ( string _id ) { id = _id; }
    void setAlias ( string a ) { alias = a; }
    void setPassword ( string p ) { password = p; }
    void setRoundNum ( int rn ) { round_num = rn; }
    void setPlayerList ( vector<Player*> pl ) { player_list = pl; }
    void setWidth ( int w ) { width = w; }
    void setHeight ( int h ) { height = h; }
    int getSize(){
        return squares.size();
    }
    vector<QString> getlast(){ return serverinfo;}
    void setLast(vector<QString> lol){
       serverinfo = lol;
       string lulz = to_string(serverinfo.size());
       qDebug() << QString::fromStdString(lulz);
    }
    Structure *resourceCheck(Player *owner,string type);
};

// implement a command structure
class Command{
public:
    virtual bool execute()=0;

};
//fortress/road construction
class buildCommand: public Command{
private:
    int id;
public:
    buildCommand(int newId){
        id = newId;
    }

    bool execute();
};
//when a square is unmade
class destroyCommand: public Command{
private:
    int id;
public:
    destroyCommand(int newId){
        id = newId;
    }
    bool execute();
};
//gathering resources
class resourceCommand: public Command{
private:
    int resources;
    int squareid;
    int playerId;
public:
    resourceCommand(int id1,int id2){
        squareid = id1;
        playerId = id2;
    }
    bool execute();
    int get();
    int store();
};
//creating dragons
class dragonCommand: public Command{
private:
    int playerId;
    int x;
    int y;
    int hp;
    bool status;
public:
    dragonCommand(int sendId){
        playerId = sendId;
    }
    bool execute();
    bool die();
    bool damage();
};
//for random events
class eventHandler{
    private:

    string image;
    int length;
public:
    eventHandler(){

    }

    virtual bool execute() = 0;
};

#endif // GAMEMODEL_
