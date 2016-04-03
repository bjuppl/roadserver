#include "control.h"
#include "utils.h"
#include <QDebug>
using namespace  std ;

Control *Control::instance_ = NULL;
vector<Game*> Control::gameList;

Control &Control::instance() {
    if  (instance_ == NULL ) {
        instance_ = new Control();
    }
    return *instance_;
}

Game *Control::getGameById(string id){
    for ( size_t i=0; i<gameList.size(); i++ ) {
        if ( gameList[i]->getId() == id ) {
            return gameList[i];
        }
    }
    return nullptr;
}

vector<QString> Control::levelMaker(QString gamedata){
    vector<string> levlstr;
    qDebug() << gamedata;
    string gamedata1 = gamedata.toStdString();
    levlstr = split(gamedata1,' ');
    string levelget = levlstr.back();
    string gname = levlstr.at(1);
    string gpass = levlstr.at(2);
    qDebug() << QString::fromStdString(levelget);
    if (levelget == "five"){
     ifstream stream("/home/user/roadserver/twoplayer.rr");
     vector<QString> stuff;
     stuff.push_back("NG ");
     int i = 1;
     Control::top()->setAlias(gname);
     Control::top()->setPassword(gpass);
     while(i < levlstr.size()){
         stuff.push_back(QString::fromStdString(levlstr.at(i)));
         stuff.push_back(" ");
         i++;
     }
     i = 0;
     if(stream.is_open()){
         string str1 = " ";
         squareinfo.push_back("CG ");
         while(getline(stream,str1)){
         QString proc = QString::fromStdString(str1);
         qDebug() << proc;
         stuff.push_back(proc);
         stuff.push_back(" ");
         squareinfo.push_back(proc);
         squareinfo.push_back(" ");
         }
     }
     return stuff;
    }
    if(levelget == "seven"){
        ifstream stream("/home/user/roadserver/fourplayer.rr");
        vector<QString> stuff;
        stuff.push_back("NG ");
        int i = 1;
        Control::top()->setAlias(gname);
        Control::top()->setPassword(gpass);
        while(i < levlstr.size()){
            stuff.push_back(QString::fromStdString(levlstr.at(i)));
            stuff.push_back(" ");
            i++;
        }
        i = 0;
        if(stream.is_open()){
            string str1 = " ";
            while(getline(stream,str1)){
            QString proc = QString::fromStdString(str1);
            qDebug() << proc;
            stuff.push_back(proc);
            stuff.push_back(" ");
            }
        }
        Control::top()->setLast(stuff);
        return stuff;
    }
    if(levelget == "random"){

    }

}


Game *Control::getGameByAlias(string alias){
    for ( size_t i=0; i<gameList.size(); i++ ) {
        if ( gameList[i]->getAlias() == alias ) {
            return gameList[i];
        }
    }
    return nullptr;
}

string Control::clientCommandResponse(vector<string> command, QTcpSocket *client) {

    vector<Player*> clients;

    bool game_init_error = false,
            alias_fail = false,
            password_fail = false,
            name_fail = false,
            bad_request = false;
    const string ERR_GAME_INIT = "game_init_error",
            ERR_ALIAS_FAIL = "alias_fail",
            ERR_PASS_FAIL = "password_fail",
            ERR_NAME_FAIL = "name_fail",
            ERR_BAD_REQUEST = "bad_request";

    if ( command.size() == 0) {
        game_init_error = true;
        return ERR_GAME_INIT;
    }

    const string NEW_GAME = "new_game",
            JOIN = "join",
            GAME = "game";

    //handle the first line
    if ( command.at(0) == NEW_GAME ) {

        const string ALIAS = "alias",
                PASSWORD = "password",
                PLAYER_CNT = "players",
                NAME = "name",
                LEVEL = "level";
        string alias = "",
                password = "",
                name = "";

        size_t player_cnt = 0, level = 6;

        for ( size_t i=1; i<command.size(); i++ ) {
            vector<string> line;
            line = split(command[i],' ');
            if ( line.size() < 2) {
                game_init_error = true;
                break;
            }
            if ( line[0] == ALIAS) {
                alias = line[1];
            } else if ( line[0] == PASSWORD ) {
                password = line[1];
            } else if ( line[0] == NAME) {
                name = line[1];
            } else if ( line[0] == LEVEL ) {
                try {
                    level = stoi(line[1]);
                } catch (...) {
                    game_init_error = true;
                    break;
                }
            } else if ( line[0] == PLAYER_CNT ) {
                try {

                    player_cnt = stoi(line[1]);
                } catch (... ) {
                    game_init_error = true;
                    break;
                }
            }
        }

        if ( alias == "" || player_cnt < 0 || player_cnt > 4 || name == "" ) {
            game_init_error = true;
        }

        if ( game_init_error ) {
            return ERR_GAME_INIT;
        }

        if ( getGameByAlias(alias) != nullptr ) {
            alias_fail = true;
            return ERR_ALIAS_FAIL;
        }

        Game *game = launch();

        game->setAlias(alias);
        game->setPassword(password);

        vector<Player*> plist;
        plist.push_back(new Player(name));
        plist.at(0)->setConnection(client);

        for ( size_t i=1; i<player_cnt; i++ ) {
            plist.push_back(nullptr);
        }

        game->setPlayerList(plist);

        clients.push_back(plist[0]);
        clients_affected = clients;

        game->level_manager->setLevel(level);

        return "game_init " + game->getId();

    } else {
          vector<string> fl;
          fl = split(command.at(0), ' ');
          if ( fl.size() < 1) {
              game_init_error = true;
              return ERR_GAME_INIT;
          }
          if ( fl.at(0) == JOIN) {
            if ( fl.size() < 2) {
                game_init_error = true;
                return ERR_GAME_INIT;
            }
            string alias = fl.at(1);
                const string ALIAS = "alias",
                        PASSWORD = "password",
                        NAME = "name";
                string aliasj = "",
                        password = "",
                        name = "";

                for ( size_t i=1; i<command.size(); i++ ) {
                    vector<string> line;
                    line = split(command[i],' ');
                    if ( line.size() < 2) {
                        game_init_error = true;
                        break;
                    }
                    if ( line[0] == ALIAS) {
                        aliasj = line[1];
                    } else if ( line[0] == PASSWORD ) {
                        password = line[1];
                    } else if ( line[0] == NAME ) {
                        name = line[1];
                    }
                }

                Game *game = getGameByAlias(aliasj);

                if ( aliasj == "" || name == "" ) {
                    game_init_error= true;
                    return ERR_GAME_INIT;
                }
                // Failure to join: either game does not exist, or is not waiting for new members.

                if ( game == nullptr || game->expectedPlayerNum() == -1 ) {
                    alias_fail = true;
                    return ERR_ALIAS_FAIL;
                }
                if ( game->getPassword().size() > 0 && game->getPassword() != password ) {
                    password_fail = true;
                    return ERR_PASS_FAIL;
                }
                if ( game->getPlayer(name) != nullptr ) {
                    password_fail = true;
                    return ERR_PASS_FAIL;
                }

                vector<Player*> modPlist;
                modPlist = game->getPlayerList();
                Player *pl = new Player(name);
                pl->setConnection(client);
                modPlist[game->expectedPlayerNum()] = pl;
                game->setPlayerList(modPlist);

                for ( size_t i=0; i<modPlist.size(); i++ ) {
                    if ( modPlist.at(i) != nullptr) {
                        clients.push_back(modPlist[i]);
                    }
                }

                clients_affected = clients;

                string ret =  "game_joined " + game->getId() + "\n";
                ret += "player_list";
                for ( size_t i=0; i<game->getPlayerList().size(); i++ ) {
                    Player *pl =  game->getPlayerList().at(i);
                    if (pl == nullptr) {
                        break;
                    } else {
                        ret += " " + pl->getName();
                    }
                }

                if ( game->expectedPlayerNum() == -1 ) {
                    ret += "\nstart_game";
                }

                return ret;

          } else if (fl.at(0) == GAME) {
                if ( fl.size() < 4) {
                    bad_request = true;
                    return ERR_BAD_REQUEST;
                }
                Game *game = getGameById(fl.at(1));
                Player *player;
                if ( game == nullptr || (player = game->getPlayer(fl.at(3))) == nullptr || game->expectedPlayerNum() > -1) {
                    bad_request = true;
                    return ERR_BAD_REQUEST;
                }

                clients = game->getPlayerList();
                clients_affected = clients;

          }
    }

    return "";

}

vector<QTcpSocket*> Control::getAffectedSockets(QTcpSocket *main_client) {
    vector<QTcpSocket*> ret;
    bool main_is_player = false;
    for ( size_t i=0; i<clients_affected.size();i++ ) {
        if ( clients_affected.at(i)->getConnection() == main_client ) {
            main_is_player = true;
        }
        ret.push_back(clients_affected.at(i)->getConnection());
    }
    if ( !main_is_player) {
        ret.push_back(main_client);
    }
    return ret;

}

Game *Control::launch() {

    //figure out an ID
    //The ID space is 10^45, so the odds of a duplicate are somewhat low.
    string id;
    id = to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999)) +
            to_string(random_int(0,99999));

   return launch(id);
}

Game *Control::launch(string id ) {
    Game *game = new Game(id);
    gameList.push_back(game);
    return game;
}
