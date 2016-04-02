#ifndef CONTROL_H
#define CONTROL_H

#include "gamefile.h"

using namespace std;
class Control {

    static vector<Game*> gameList;
    static Control *instance_;
    Control(){}

public:
    static Control &instance();
    static Game *top() { return gameList.size() == 0 ? nullptr : gameList[gameList.size()-1]; }
    static Game *getGameById ( string id );
    static Game *getGameByAlias ( string alias );
    Game *launch();
    Game *launch(string id);

    string clientCommandResponse ( vector<string> command );



};

#endif // CONTROL_H
