#include "listener.h"
#include <string>
#include "utils.h"
#include "control.h"
Switchboard *Switchboard::instance_ = NULL;
Switchboard &Switchboard::instance() {
    if ( instance_ == NULL ) {
        instance_ = new Switchboard;
    }
    return *instance_;
}
QString Switchboard::squareSender(string str1, string id, string playername){
    //Str1 should contain the sqr number, type e.g. "X,Y Fo"
  QString msg = "Ct";
  msg += QString::fromStdString(id) + " ";
  msg += QString::fromStdString(playername) + " assign ";
  QString squarestr = QString::fromStdString(str1);
  msg+= squarestr;
  return msg;

}
QString Switchboard::structSender(string str1, string id, string playername){
    //Str1 should contain the sqr number, type, and struct type
    QString msg;
    msg += QString::fromStdString(id) + " ";
    msg += QString::fromStdString(playername) + " assign ";
    QString structstr = QString::fromStdString(str1);
    msg+= structstr;
    return msg;
}

QString Switchboard::gameSend(QString info){
    string infos = info.toStdString();
    vector<string> infovec = split(infos,' ');
    string gname = Control::top()->getAlias();
    string gpass = Control::top()->getPassword();
    QString result;
    if(gname == infovec.at(1) && gpass == infovec.at(2)){
        result += QString::fromStdString(gname) + " " + QString::fromStdString(gpass) + " " + QString::fromStdString(infovec.at(3));
        Player *newplayer = new Player(infovec.at(3));
    }
    else{
        result = "gamenotfound";
    }
    return result;
}
