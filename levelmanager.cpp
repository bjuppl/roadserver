#include "levelmanager.h"
#include "gamemodel.h"
#include "gamefile.h"
#include <iostream>
#include <istream>
#include <QDebug>
//#include "squarelabel.h"
//LevelManager *LevelManager::instance_ = nullptr;

/*LevelManager& LevelManager::instance() {
    if (instance_ == nullptr ) {
        instance_ = new LevelManager();
    }

    return *instance_;
}*/

std::vector<std::string> LevelManager::getLevel(int num) {
    std::vector<std::string> contents;

    string levie = "";
    switch ( num ) {
        case 1:
            levie = "Pl,No,No Ri,No,No Fo,No,No Ca,No,No Pl,No,No Ri,No,No Ca,No,No Mo,No,No \
                    Fo,No,No Ri,No,No Ca,No,No Mo,No,No Ca,No,No Fo,No,No Fo,No,No Ri,No,No \
                    Fo,No,No Ri,No,No Pl,No,No Pl,No,No Pl,No,No Mo,No,No Ri,No,No Mo,No,No \
                    Ri,No,No Pl,No,No Fo,No,No Ca,No,No Pl,No,No Ca,No,No Fo,No,No Mo,No,No \
                    Ri,No,No Ri,No,No Mo,No,No Fo,No,No Wi,No,No Pl,No,No Ri,No,No Pl,No,No \
                    Ca,No,No Ca,No,No Pl,No,No Fo,No,No Pl,No,No Pl,No,No Ri,No,No Ri,No,No \
                    Fo,No,No Fo,No,No Fo,No,No Ca,No,No Fo,No,No Ri,No,No Ri,No,No Mo,No,No \
                    Ri,No,No Ri,No,No Pl,No,No Fo,No,No Ri,No,No Mo,No,No Ca,No,No Pl,No,No ";
            break;
    case 2:
        levie = "Pl,No,No Ca,No,No Fo,No,No Pl,No,No Fo,No,No Ri,No,No Ca,No,No Fo,No,No \
                Pl,No,No Ca,No,No Fo,No,No Ca,No,No Mo,No,No Mo,No,No Fo,No,No Ri,No,No \
                Ca,No,No Fo,No,No Pl,No,No Mo,No,No Fo,No,No Ri,No,No Ca,No,No Mo,No,No \
                Pl,No,No Fo,No,No Ri,No,No Ri,No,No Pl,No,No Fo,No,No Mo,No,No Pl,No,No \
                Ri,No,No Ri,No,No Fo,No,No Ri,No,No Ri,No,No Ca,No,No Ca,No,No Mo,No,No \
                Fo,No,No Ca,No,No Pl,No,No Ca,No,No Ri,No,No Ca,No,No Pl,No,No Mo,No,No \
                Mo,No,No Pl,No,No Pl,No,No Pl,No,No Mo,No,No Fo,No,No Ri,No,No Ca,No,No \
                Pl,No,No Ca,No,No Ca,No,No Fo,No,No Ca,No,No Ca,No,No Ca,No,No Fo,No,No ";
        break;
    case 3:
        levie = "Fo,No,No Ca,No,No Fo,No,No Pl,No,No Ri,No,No Ca,No,No Fo,No,No Ri,No,No \
                Pl,No,No Pl,No,No Ri,No,No Pl,No,No Fo,No,No Pl,No,No Fo,No,No Ri,No,No \
                Ri,No,No Pl,No,No Mo,No,No Fo,No,No Mo,No,No Pl,No,No Fo,No,No Pl,No,No \
                Ca,No,No Ca,No,No Ri,No,No Pl,No,No Pl,No,No Ri,No,No Ri,No,No Pl,No,No \
                Ri,No,No Mo,No,No Ri,No,No Fo,No,No Pl,No,No Mo,No,No Ri,No,No Fo,No,No \
                Pl,No,No Pl,No,No Mo,No,No Mo,No,No Fo,No,No Ca,No,No Mo,No,No Pl,No,No \
                Ca,No,No Pl,No,No Ca,No,No Ca,No,No Ca,No,No Fo,No,No Mo,No,No Ri,No,No \
                Ri,No,No Pl,No,No Mo,No,No Pl,No,No Pl,No,No Pl,No,No Pl,No,No Fo,No,No ";
        break;
    case 4:
        levie = "Ri,No,No Fo,No,No Ri,No,No Ca,No,No Ri,No,No Ca,No,No Pl,No,No Ri,No,No \
                Ri,No,No Pl,No,No Pl,No,No Fo,No,No Mo,No,No Ca,No,No Ca,No,No Fo,No,No \
                Fo,No,No Ca,No,No Pl,No,No Fo,No,No Mo,No,No Ri,No,No Ca,No,No Pl,No,No \
                Mo,No,No Ca,No,No Ri,No,No Mo,No,No Ca,No,No Fo,No,No Fo,No,No Pl,No,No \
                Ca,No,No Ca,No,No Ca,No,No Pl,No,No Ca,No,No Ri,No,No Fo,No,No Fo,No,No \
                Pl,No,No Pl,No,No Ri,No,No Ca,No,No Fo,No,No Pl,No,No Ri,No,No Fo,No,No \
                Pl,No,No Mo,No,No Ri,No,No Ca,No,No Ri,No,No Ri,No,No Ri,No,No Ca,No,No \
                Pl,No,No Ri,No,No Fo,No,No Fo,No,No Pl,No,No Ri,No,No Ri,No,No Ca,No,No ";
        break;
    case 5:
        levie = "Ca,No,No Ri,No,No Pl,No,No Ca,No,No Ca,No,No Pl,No,No Mo,No,No Fo,No,No \
                Pl,No,No Ri,No,No Ri,No,No Ca,No,No Ca,No,No Pl,No,No Ca,No,No Ri,No,No \
                Fo,No,No Ca,No,No Ca,No,No Ri,No,No Mo,No,No Mo,No,No Fo,No,No Ri,No,No \
                Pl,No,No Ri,No,No Ca,No,No Ri,No,No Pl,No,No Mo,No,No Ca,No,No Ri,No,No \
                Mo,No,No Pl,No,No Ri,No,No Ca,No,No Ca,No,No Mo,No,No Ri,No,No Fo,No,No \
                Ri,No,No Fo,No,No Pl,No,No Fo,No,No Pl,No,No Ca,No,No Pl,No,No Mo,No,No \
                Ri,No,No Ri,No,No Fo,No,No Mo,No,No Ca,No,No Ca,No,No Fo,No,No Pl,No,No \
                Pl,No,No Mo,No,No Pl,No,No Pl,No,No Mo,No,No Fo,No,No Ca,No,No Ri,No,No ";
        break;
    case 6:
        levie = "Ri,No,No Pl,No,No Fo,No,No Mo,No,No Pl,No,No Ri,No,No Mo,No,No Pl,No,No \
                Mo,No,No Ca,No,No Ca,No,No Pl,No,No Pl,No,No Ri,No,No Mo,No,No Mo,No,No \
                Ri,No,No Fo,No,No Ca,No,No Pl,No,No Mo,No,No Pl,No,No Ri,No,No Pl,No,No \
                Mo,No,No Ri,No,No Pl,No,No Ri,No,No Ca,No,No Ca,No,No Ri,No,No Ca,No,No \
                Mo,No,No Mo,No,No Ri,No,No Pl,No,No Mo,No,No Mo,No,No Mo,No,No Ri,No,No \
                Pl,No,No Ri,No,No Fo,No,No Mo,No,No Ri,No,No Ri,No,No Mo,No,No Pl,No,No \
                Ri,No,No Mo,No,No Ri,No,No Pl,No,No Ca,No,No Mo,No,No Ca,No,No Ca,No,No \
                Mo,No,No Ca,No,No Ri,No,No Mo,No,No Fo,No,No Fo,No,No Ca,No,No Pl,No,No ";
        break;

    }

    contents = split(levie,'\n');

    return contents;

}

std::vector<int> LevelManager::getPlayerCoords(Player *player){
    for ( size_t i=0; i<game->getPlayerList().size(); i++ ) {
        if ( game->getPlayerList().at(i) == player ) {
            switch(i) {
            case 0: return {0,0}; break;
            case 1: return {x,y}; break;
            case 2: return {x,0}; break;
            case 3: return {0,y}; break;

            }
        }
    }
    return {-1,-1};
}

std::vector<std::string> LevelManager::getLevel(std::string level ) {
    std::vector<std::string> contents;
    const std::string test = "test";
    const std::string seven = "seven";
    if ( level == test ) {
        int o = 1;
        if ( o == 1 ) { contents = resourceFileContents("single-player"); }
        else { contents = resourceFileContents("sampleGame"); }
    }
    if (level == seven){
        contents = resourceFileContents("seven");
    }
    return contents;

}

std::vector<std::string> LevelManager::resourceFileContents(std::string alias ) {
    QFile file(QString::fromStdString(":/" + alias));
    std::vector<std::string> ret;
    if(file.open(QFile::ReadOnly)) {
        QTextStream conts(&file);

        while(!conts.atEnd()) {
            QString ln = conts.readLine();
            ret.push_back(ln.toStdString());
        }

        file.close();

        return ret;

    } else {
        std::cerr << "Failed to read resource file: '" << alias << "'. " << std::endl;

        return ret;
    }
}
string LevelManager::upRec(int goodRes){
    string result;
    if(goodRes == 0){
        int wood = game->getCurPlayer()->getWood();
        wood += 50;
        game->getCurPlayer()->setWood(wood);
        result = "wood";
        return result;
    }
    if(goodRes == 1){
        int gold = game->getCurPlayer()->getGold();
        gold += 50;
        game->getCurPlayer()->setGold(gold);
        result = "gold";
        return result;
    }
    if(goodRes == 2){
        int water = game->getCurPlayer()->getWater();
        water += 50;
        game->getCurPlayer()->setWater(water);
        result = "water";
        return result;
    }
    if(goodRes == 3){
        int stone = game->getCurPlayer()->getStone();
        stone += 50;
        game->getCurPlayer()->setStone(stone);
        result = "stone";
        return result;
    }
}
string LevelManager::downRec(int badRes){
    string result;
    if(badRes == 0){
        int wood = game->getCurPlayer()->getWood();
        wood -= 50;
        game->getCurPlayer()->setWood(wood);
        result = "wood";
        return result;
    }
    if(badRes == 1){
        int gold = game->getCurPlayer()->getGold();
        gold -= 50;
        game->getCurPlayer()->setGold(gold);
        result = "gold";
        return result;
    }
    if(badRes == 2){
        int water = game->getCurPlayer()->getWater();
        water -= 50;
        game->getCurPlayer()->setWater(water);
        result = "water";
        return result;
    }
    if(badRes == 3){

        int stone = game->getCurPlayer()->getStone();
        stone -= 50;
        game->getCurPlayer()->setStone(stone);
        result = "stone";
        return result;
    }
}
bool LevelManager::killStruct(int hit, int wid){
    Square *victim = game->getSquare(wid,hit);
    if (victim->getAddition()!= "No"){
    Structure *killStruct = game->getStructure("Ru");
    victim->setStruct(killStruct);
    victim->setAddition("No");
    //SquareLabel *vicLbl = victim->getLabel();
    //int size = GuiManager::instance().getUi()->gridLayoutWidget->width()/game->getSize()/2;
     //QSize size1(size,size);
    //vicLbl->setPixmap(GuiManager::instance().setmap(victim,size1));
    return true;
    }
    else{
        return false;
    }
}
bool LevelManager::riverSquare(int hit, int wid){
    Square *victim = game->getSquare(wid,hit);
    Structure *killStruct = game->getStructure("Ru");
    if(victim->getImage() != "Ri"){
    victim->setStruct(killStruct);
    victim->setAddition("No");
    victim->setType("Ri");
    victim->setImage("Ri");
    //SquareLabel *vicLbl = victim->getLabel();
    //int size = GuiManager::instance().getUi()->gridLayoutWidget->width()/game->getSize()/2;
     //QSize size1(size,size);
    //vicLbl->setPixmap(GuiManager::instance().setmap(victim,size1));
    return true;
    }
    else{
        return false;
    }
}
bool LevelManager::burnSquare(int hit, int wid){
    Square *victim = game->getSquare(wid,hit);
    Structure *killStruct = game->getStructure("Ru");
    if(victim->getImage() != "Pl"){
    victim->setStruct(killStruct);
    victim->setAddition("No");
    victim->setType("Pl");
    victim->setImage("Pl");
    //SquareLabel *vicLbl = victim->getLabel();
    //int size = GuiManager::instance().getUi()->gridLayoutWidget->width()/game->getSize()/2;
     //QSize size1(size,size);
    //vicLbl->setPixmap(GuiManager::instance().setmap(victim,size1));
    return true;
    }
    else{
        return false;
    }
}
bool LevelManager::quakeSquare(int hit, int wid){
    Square *victim = game->getSquare(wid,hit);
    Structure *killStruct = game->getStructure("Ru");
    if(victim->getImage() != "Ca"){
    victim->setStruct(killStruct);
    victim->setAddition("No");
    victim->setType("Ca");
    victim->setImage("Ca");
    //SquareLabel *vicLbl = victim->getLabel();
    //int size = GuiManager::instance().getUi()->gridLayoutWidget->width()/game->getSize()/2;
     //QSize size1(size,size);
    //vicLbl->setPixmap(GuiManager::instance().setmap(victim,size1));
    return true;
    }
    else{
        return false;
    }
}
