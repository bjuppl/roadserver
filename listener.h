#ifndef LISTENER_H
#define LISTENER_H

#include <vector>
#include <string>

#include <gamemodel.h>

class Switchboard {

private:
//    vector<Game*> activeGames;
    static Switchboard *instance_;
    Switchboard(){}
public:
    static Switchboard &instance();
    QString actionSender(QString str1);
};


#endif // LISTENER_H
