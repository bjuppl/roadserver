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
    QString squareSender(string str1, string id, string playername);
    QString structSender(string str1, string id, string playername);
    QString gameSend(QString info);
};


#endif // LISTENER_H
