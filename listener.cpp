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
QString Switchboard::actionSender(QString str1){
    string str = str1.toStdString();
    string compstr1;
    string compstr2;
    compstr1 += str.at(0);
    compstr2 += str.at(1);
    if (compstr1 == "N" && compstr2 =="O"){
        string xstr;
        xstr += str.at(10);
        string ystr;
        ystr += str.at(12);
        string msgstr;
        msgstr += xstr + "," + ystr;
        string plstr;
        int index = 35;
        while(index < (str.size()-1)){
            plstr += str.at(index);
            index++;
        }
        msgstr += plstr;
        QString result;
        result += "assign " + QString::fromStdString(msgstr);
        return result;
    }
    if (compstr1 == "N" && compstr2=="S"){
        string xstr;
        xstr += str.at(10);
        string ystr;
        ystr += str.at(12);
        string msgstr;
        msgstr += xstr + "," + ystr;
        string plstr;
        int index = 23;
        while(index < (str.size())){
            plstr += str.at(index);
            index++;
        }
        msgstr += plstr;
        QString result;
        result += "assign " + QString::fromStdString(msgstr);
        return result;
    }
    if (compstr1 == "S" && compstr2=="B"){
        string xstr;
        xstr += str.at(10);
        string ystr;
        ystr += str.at(12);
        string msgstr;
        msgstr += xstr + "," + ystr;
        string plstr;
        int index = 25;
        while(index < (str.size())){
            plstr += str.at(index);
            index++;
        }
        msgstr += plstr;
        QString result = QString::fromStdString(msgstr);
        return result;
    }
    if (compstr1 == "N" && compstr2=="T"){
        string xstr;
        xstr += str.at(10);
        string ystr;
        ystr += str.at(12);
        string msgstr;
        msgstr += xstr + "," + ystr;
        string plstr;
        int index = 28;
        while(index < (str.size())){
            plstr += str.at(index);
            index++;
        }
        msgstr += plstr;
        QString result = QString::fromStdString(msgstr);
        return result;
    }
    if (compstr1 == "N" && compstr2 == "R"){
        string result;
        vector<string> strs = split(str,' ');
        result += strs.at(1);
        int i = 2;
        while(i< strs.size()){
            if (strs.at(i) != "assign" || strs.at(i) != "resources"){
                result+= strs.at(i);
            }
            i++;
        }
        return QString::fromStdString(result);
    }
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
