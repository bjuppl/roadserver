#ifndef PLAYER_H
#define PLAYER_H
#include "square.h"
#include <string>
#include <vector>
#include <QTcpSocket>

class Square;

class Player
{
private:
    std::string color;
    int goldCount=0, woodCount=0, stoneCount=0, waterCount=0;
    int score;
    int startTime;
    std::string name = "";
    std::vector<Square*> squareList;

    QTcpSocket *connection;

    bool active{false};
public:
    Player(std::string newName) : color("black"), goldCount(0), woodCount(0), stoneCount(0), waterCount(0),name(newName) { startTime = 0; }
       void setName(std::string name2){ name = name2;}
       std::string getName(){ return name; }
       int getWood(){ return woodCount;}
       int getStone(){ return stoneCount; }
       int getWater(){ return waterCount; }
       int getGold(){  return goldCount;}
       int getScore(){  return score;}
       int getStartTime(){  return startTime;}
       int getResource (std::string type );
       std::string getColor () { return color; }
       std::vector<Square*> getSquares(){ return squareList; }
       QTcpSocket *getConnection() { return connection; }
       bool isActive() { return active; }

       void setActive(bool a ) { active = a; }
       void setConnection( QTcpSocket *c) { connection = c; }
       void setColor( std::string c) { color = c; }
       void setResource(std::string type, int amt );
       void incResource(std::string type, int amt );
       void setWood(int newWood){ woodCount = newWood;}
       void setGold(int gold){ goldCount = gold;}
       void setStone(int stone){ stoneCount = stone; }
       void setWater(int water){ waterCount = water;}
       void setScore(int sc){ score = sc;}
       void setStartTime(int st){ startTime = st;}
};


#endif // PLAYER_H
