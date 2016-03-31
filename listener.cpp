#include "listener.h"
#include <string>
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
        QString result = QString::fromStdString(msgstr);
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
        QString result = QString::fromStdString(msgstr);
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
}
