#ifndef CONTROL_H
#define CONTROL_H

#include "gamefile.h"

using namespace std;
class Control {

    vector<Game*> gameList;
    static Control *instance_;
    Control(){}

public:
    static Control &instance;
    void launch();
    void launch(string id);



};

#endif // CONTROL_H
