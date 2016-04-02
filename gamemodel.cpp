#include <string>
#include <iostream>
#include <istream>
#include <random>
#include <QMessageBox>
#include "gamemodel.h"
//#include "gui.h"
#include "player.h"
#include "square.h"
#include "levelmanager.h"
using namespace std;

class Player;
int random_int(int min, int max) {
    static std::default_random_engine engine { std::random_device{}() };
    std::uniform_int_distribution<int> distro{min, max};
    return distro(engine);
}

Game::Game(string id_) : id(id_)  {
    updater = new Updater(this);
    level_manager = new LevelManager(this);
    vector<Resource*> rl;


    vector<Structure*> sl;
    //Bo = boat, Br = bridge, Wa = wall, Tu = tunnel
    vector<Price> a = {Price(this, "Wo",100),Price(this, "St",50)};
    sl.push_back(new Structure(this, "boat","Bo",a));
    vector<Price> b = {Price(this,"Wo",200),Price(this,"St",100)};
    sl.push_back(new Structure(this,"bridge","Br",b));
    vector<Price> c = {Price(this,"Wo",50),Price(this,"St",300)};
    sl.push_back(new Structure(this,"wall","Wa",c));
    vector<Price> d = {Price(this,"Wa",50),Price(this,"Go",100),Price(this,"St",50)};
    sl.push_back(new Structure(this,"tunnel","Tu",d));
    vector<Price> e = {Price(this,"Go",100),Price(this,"Wa",75)};
    sl.push_back(new Structure(this,"deforest","De",e));
    vector<Price> f = {Price(this,"",0)};
    sl.push_back(new Structure(this,"ruins","Ru",f));
    structure_types = sl;

}

void Game::start(){
    updater->start();

}

void Game::updateResources() {
    for ( size_t i=0; i<player_list.size(); i++ ) {
        vector<Square*> mysquares;
        Player *p = player_list[i];
        mysquares = getPlayerSquares(p);
        for ( size_t j=0; j<mysquares.size(); j++ ) {
            if(mysquares.at(j)->getType() != "Wi")
            {
                std::string rtype = mysquares.at(j)->getResourceType();
                int add = getResource(rtype)->value;

                p->incResource(rtype, add);
            }
        }
    }
}

vector<Square*> Game::getPlayerSquares(Player *owner) {
    vector<Square*> list;

    if ( owner == NULL ) {
        return list;
    }
    for ( size_t i=0; i<squares.size(); i++ ) {
        for ( size_t j=0; j<squares[i].size(); j++ ) {
            if (squares[i][j]->getOwner() != NULL && squares[i][j]->getOwner()->getName() == owner->getName() ) {
                list.push_back(squares[i][j]);

            }
        }
    }

    return list;
}



//used for construction of bridges/roads
bool buildCommand::execute(){
    return true;
}

Game::~Game() {
    for ( size_t i=0; i<player_list.size(); i++ ) {
        delete player_list[i];
    }
    for ( size_t i=0; i<squares.size(); i++ ) {
        for ( size_t j=0; j<squares.at(i).size(); j ++ ) {
            delete squares[i][j];
        }
    }
    for ( size_t i=0; i<resource_types.size(); i++ ) {
            delete resource_types.at(i);
    }

}

//save the game by writing to a file
bool Game::save(){
    return true;
}

//load a previous game state
string Game::load(){
    return "string";
}

//update the game world
void Game::update(){
    this->updateResources();
    //GuiManager::instance().fillResourceList();
    //GuiManager::instance().setTimeBox( Updater::instance().getDuration()/1000 );
}

bool Game::applyCommand(string command) {
    std::vector<std::string> itms;
    itms = split(command,' ');

    std::string identifier = itms[0];

    const std::string scores = "scores",
            start = "start",
            end = "end";
    if ( identifier == scores) {

    } else if ( identifier == start ) {

    } else if ( identifier == end ) {

    } else {

    }

    return true;
}

/*Game& Game::instance() {
    if (instance_ == NULL ) {
        instance_ = new Game();
    }
    return *instance_;
}*/


void Game::purchaseAddition(Square *source) {

}

void Game::setGameLoader(GameFileManager *gfm) {
    delete gfm;
    loader = gfm;
}

Player *Game::getPlayer(string name){

    for ( size_t i=0; i<player_list.size(); i++ ) {
        if ( player_list[i]->getName() == name   ) {
            return player_list[i];
        }
    }

    return NULL;
}

Resource *Game::getResource(string shortName) {
    for ( size_t i=0; i<resource_types.size(); i++ ) {
        if ( resource_types[i]->shortName == shortName ) {
            return resource_types[i];
            cout<<"ok";
        }
    }
    return nullptr;
}

Structure *Game::getStructure(string shortName) {
    for ( size_t i=0; i<structure_types.size(); i++ ) {
        if ( structure_types[i]->shortName == shortName ) {
            return structure_types[i];
        }
    }
    return nullptr;
}

Square *Game::getSquare(int id) {
   for (size_t i=0; i<squares.size(); i++ ) {
         for ( size_t j=0; j<squares.at(i).size(); j++ ) {
            if (squares.at(i).at(j)->getId() == id ) {
                return squares.at(i).at(j);
            }
        }
   }

  return nullptr;
}


void Game::setSquares ( vector<vector<Square*>> sq ) {
    for ( size_t i=0; i<squares.size(); i++ ) {
        for (size_t j=0; j<squares.at(i).size(); j++ ) {
            delete squares[i][j];
        }
    }
    squares = sq;
}


void Game::setResources(vector<Resource *> vr) {
    for ( size_t i=0; i< resource_types.size(); i++ ) {
            delete resource_types[i];
    }
    resource_types = vr;
}
void Updater::eventrun(){
    if (game->level_manager->getRand()){
        int random = random_int(0,6);
        if(random == 0){
          //spontaneously give a player 50 of a resource
            int goodInt = random_int(0,3);
            string recType = game->level_manager->upRec(goodInt);
            string name = game->getCurPlayer()->getName();
            QString displayName;
            QString displayResc;
            displayResc = displayResc.fromStdString(recType);
            displayName = displayName.fromStdString(name);
            //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Random Event!",displayName + " has had an unusually productive cycle. +50 " + displayResc + ".",0,0);
        }
        if(random == 1){
         //retract 50 of a resource
            int badInt = random_int(0,3);
            string recType = game->level_manager->downRec(badInt);
            string name = game->getCurPlayer()->getName();
            QString displayName;
            QString displayRec;
            displayRec = displayRec.fromStdString(recType);
            displayName = displayName.fromStdString(name);
            //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Random Event!",displayName + " has just gotten robbed! Oh dear. -50" + displayRec + ".",0,0);
        }
        if(random == 2){
         //remove a structure
          int height = game->getHeight();
          int width = game->getWidth();
          int rndWid = random_int(0,width-1);
          int rndHei = random_int(0,height-1);
          bool foo = game->level_manager->killStruct(rndHei,rndWid);
          if (foo == true){
          QString ht = ht.fromStdString(to_string(rndHei));
          QString wi = wi.fromStdString(to_string(rndWid));
          //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Random Event!","Oh no! A structure has just collapsed at " +  wi + "," + ht +".",0,0);
        }
        }
        if(random == 3){
        //rains fall and flood a square turning it into a river
            int height = game->getHeight();
            int width = game->getWidth();
            int rndWid = random_int(0,width-1);
            int rndHei = random_int(0,height-1);
            bool foo = game->level_manager->riverSquare(rndHei,rndWid);
            if (foo == true){
            QString ht = ht.fromStdString(to_string(rndHei));
            QString wi = wi.fromStdString(to_string(rndWid));
            //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Random Event!","Oh no! Heavy rains have turned the square at " +  wi + "," + ht +" into a river, washing away any progress!.",0,0);
          }
        }
        if(random == 4){
        //a non plain square burns away, leaving a plain
            int height = game->getHeight();
            int width = game->getWidth();
            int rndWid = random_int(0,width-1);
            int rndHei = random_int(0,height-1);
            bool foo = game->level_manager->burnSquare(rndHei,rndWid);
            if (foo == true){
            QString ht = ht.fromStdString(to_string(rndHei));
            QString wi = wi.fromStdString(to_string(rndWid));
            //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Random Event!","Oh no! Flames have burnt " +  wi + "," + ht +" to a crisp! Only some grass remains.",0,0);

        }
        }
        if(random == 5){
        //earthquake turns a square into a canyon
            int height = game->getHeight();
            int width = game->getWidth();
            int rndWid = random_int(0,width-1);
            int rndHei = random_int(0,height-1);
            bool foo = game->level_manager->quakeSquare(rndHei,rndWid);
            if (foo == true){
            QString ht = ht.fromStdString(to_string(rndHei));
            QString wi = wi.fromStdString(to_string(rndWid));
            //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Random Event!","Oh no! Flames have burnt " +  wi + "," + ht +" to a crisp! Only some grass remains.",0,0);
        }
        }
        if(random == 6){
            //QMessageBox::information(GuiManager::instance().getUi()->gridLayoutWidget,"Lucky","Nothing Happened.... this time.",0,0);
        }

    else{

    }
}
}


//destory a road or forturess on a square
bool destroyCommand::execute(){
   return true;
}
//load a resource node
bool resourceCommand::execute(){
   return true;
}
//get resources from the node
int resourceCommand::get(){
    return 0;
}
//store resoures in a player's "bank"
int resourceCommand::store(){
    return 0;
}
//begin the dragon's attack
bool dragonCommand::execute(){
    return true;
}
//when a dragon dies, it will be removed,but resources stolen by it are retained
bool dragonCommand::die(){
    return false;
}
//when a dragon takes damage
bool dragonCommand::damage(){
    return true;
}
//takes <newdif> and sets the duff struct accordingly

void Game::setDiff(string newdiff){
    diff = newdiff;
//sets modifiers
    if (diff == "Ez"){
        std::cout << "Easy" << std::endl;
        level_manager->getDuff()->waterMod = 20;
        level_manager->getDuff()->goldMod = 5;
        level_manager->getDuff()->woodMod = 10;
        level_manager->getDuff()->stoneMod = 7;
        std::cout << "End of easy" << std::endl;

    }
    else if (diff == "Md"){
        level_manager->getDuff()->waterMod = 15;
        level_manager->getDuff()->goldMod = 3;
        level_manager->getDuff()->woodMod = 5;
        level_manager->getDuff()->stoneMod = 3;
    }
    else {
        level_manager->getDuff()->waterMod = 10;
        level_manager->getDuff()->goldMod = 1;
        level_manager->getDuff()->woodMod = 3;
        level_manager->getDuff()->stoneMod = 1;
    }
    for (size_t i=0; i<resource_types.size(); i++ ) {
        delete resource_types[i];
    }
    //initialize resources moved to here b/c orignal positon did wierd things with the modifiers
    vector<Resource*> rl;
    rl.push_back(new Resource(this,"water","Wa",level_manager->getDuff()->waterMod));
    rl.push_back(new Resource(this,"wood","Wo",level_manager->getDuff()->woodMod));
    rl.push_back(new Resource(this,"stone","St",level_manager->getDuff()->stoneMod));
    rl.push_back(new Resource(this,"gold","Go",level_manager->getDuff()->goldMod));
    rl.push_back(new Resource(this,"[none]","",0)); //so resourceType gets can return nempty string and we know what to do with it
    resource_types = rl;

    std::cout << "OK!" << std::endl;

}
Structure *Game::resourceCheck(Player *owner,string type){
    if(type == "Ca"){

       int wood = owner->getWood();
       int stone = owner->getStone();
       if (wood >= 50 && stone >= 300){
           int newwood = (wood-50);
           int newstone = (stone-300);
           owner->setStone(newstone);
           owner->setWood(newwood);
           Structure *br = getStructure("Br");
           return br;
       }
       else{
           return nullptr;
       }
    }
    if(type == "Ri"){
        int wood = owner->getWood();
        int stone = owner->getStone();
        if (wood >= 200 && stone >= 100){
            Structure *bo = getStructure("Bo");
            int newwood = (wood-200);
            int newstone = (stone-100);
            owner->setStone(newstone);
            owner->setWood(newwood);
            return bo;
        }
        else{
            return nullptr;
        }
    }
    if(type == "Mo"){
        int water = owner->getWater();
        int stone = owner->getStone();
        int gold = owner->getGold();
        if (water >= 50 && stone >= 50 && gold >= 100){
            Structure *tu = getStructure("Tu");
            int newwater = (water-50);
            int newstone = (stone-50);
            int newgold = (gold-100);
            owner->setStone(newstone);
            owner->setWater(newwater);
            owner->setGold(newgold);
            return tu;
        }
        else{
            return nullptr;
        }
    }
    if (type == "Fo"){
        int gold = owner->getGold();
        int water = owner->getWater();
        if (water >= 75 && gold >= 100){
            Structure *de = getStructure("De");
            int newwater = (water-75);
            int newgold = (gold-100);
            owner->setWater(newwater);
            owner->setGold(newgold);
            return de;
        }
    }
    return nullptr;
}
