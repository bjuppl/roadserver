#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include "player.h"
#include "gamemodel.h"
#include <QMouseEvent>
#include <QGridLayout>
#include <QMainWindow>
#include <QHoverEvent>

//#include "squarelabel.h"

using namespace std;

class Player;
struct Structure;

//class SquareLabel;

class Square {
    static int count;
    static int size, border;
    int id;
    string type;
    string image;
    Player *owner;
    string addition;

    //SquareLabel *lbl;
    Structure *path;
    int width, height;
    int x,y;
    string color;
public:
    Square(string type_,string addition_,Player *owner_) : id(count), type(type_), image(type_), owner(owner_), addition(addition_) { count++; }
    Square(string type_,string addition_) : id(count), type(type_), image(type_), owner(NULL), addition(addition_) { count++; }
    Square(string type_) : id(count), type(type_), image(type_), owner(NULL), addition("") { count++; }
    Square(string type_,Player *owner_) : id(count), type(type_), image(type_), owner(owner_), addition("") { count++; }

    ~Square () { }
    //TODO: make Square pure virtual with inherited types.
    //This will require updating in gamefile.cpp.
    //virtual bool mine()=0;
    //virtual bool destroy()=0;

    bool hasOwner () { return owner==NULL; }
    string getType() { return type; }
    string getImage() { return image; }
    Player *getOwner() { return owner; }
    string getAddition() { return addition; }
    int getHeight () { return height; }
    int getWidth () { return width; }
    std::string getResourceType();
    int getId() { return id; }

    bool canGet(Square *prev);
    static int getSize() { return size; }
    static int getBorder() { return border; }
    //SquareLabel *getLabel () { return lbl; }

    //void setLabel( SquareLabel *l ) { lbl = l; }
    static void setSize ( int s ) { size = s; }
    static void setBorder ( int b ) { border = b; }
    void setType ( string t ) { type = t; }
    void setImage ( string i ) { image = i; }
    void setOwner ( Player *o ) { owner = o; }
    void setAddition ( string a ) { addition = a; }
    void setHeight ( int height_ ) { height = height_; }
    void setWidth ( int width_ ) { width = width_; }
    int getX(){return x;}
    int getY(){return y;}
    void setX(int nx){x = nx;}
    void setY(int ny){y = ny;}
    Structure *getStruct(){return path;}
    void setStruct(Structure *nstruct){path = nstruct;}
};

class ForestSq: public Square{

};
class MountainSq: public Square{

};
class RiverSq: public Square{

};
class PlainSq: public Square{

};
class CanyonSq: public Square{

};
class WinSq: public Square{

};

#endif // SQUARE_H
