#include "control.h"
#include "utils.h"
#include <iostream>
#include <sstream>
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
        //cout << "Request: " << alias << "; real: " << gameList[i]->getAlias() << endl;
        if ( gameList[i]->getAlias() == alias ) {
            return gameList[i];
            cout << "Match" << endl;
        } else {
            cout << "Size 1: " << alias.size() << "; size 2: " << gameList[i]->getAlias().size() << endl;
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

    const string NEW_GAME = "new_game\n",
            JOIN = "join",
            GAME = "game";

    //handle the first line

    cout <<command.at(0) << endl;

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
        //stringstream strm;
        for ( size_t i=1; i<command.size(); i++ ) {
            vector<string> line;
            line = split(command[i],'\n');
            line = split(line[0],' ');
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
        //will be over written
        plist.push_back(new Player(name));
        //plist.at(0)->setConnection(client);

        for ( size_t i=1; i<player_cnt; i++ ) {
            plist.push_back(nullptr);
        }

        game->setPlayerList(plist);

        game->level_manager->setLevel(level);


        //FYI: the application crashed EVERY TIME until I added these two cout's.
        // I don't even know what to make of it.

        GameFileManager::configureMultiplayerGame(game);

        //Although the game has [x] "players" already, we won't claim the squares to we know their real names.

        Player *fp = game->getPlayerList().at(0);
        fp->setConnection(client);
        //game->getGameLoader()->claimSquare(fp);
        game->getSquare(0,0)->setOwner(fp);
        clients.push_back(fp);
        clients_affected = clients;

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
                const string PASSWORD = "password",
                        NAME = "name";
                string aliasj = split(fl.at(1),'\n')[0],
                        password = "",
                        name = "";

                for ( size_t i=1; i<command.size(); i++ ) {
                    vector<string> line;
                    line = split(split(command[i],'\n')[0],' ');
                    if ( line.size() < 2) {
                        game_init_error = true;
                        break;
                    } else if ( line[0] == PASSWORD ) {
                        password = line[1];
                    } else if ( line[0] == NAME ) {
                        name = line[1];
                    }
                }
                cout << gameList.size() << " games available" << endl;

                /*stringstream rr;
                rr << aliasj;
                rr >> aliasj;

                rr << password;
                rr >> password;*/

                //AWFUL HACK// MUST CHANGE IMMEDIATELY
                aliasj = top()->getAlias();
                password = top()->getPassword();

                Game *game = getGameByAlias(aliasj);

                if ( aliasj == "" || name == "" ) {
                    game_init_error= true;
                            cout << "Blank name" << endl;
                    return ERR_GAME_INIT;
                }
                // Failure to join: either game does not exist, or is not waiting for new members.

                if ( game == nullptr || game->expectedPlayerNum() == -1 ) {
                    alias_fail = true;
                    if ( game == nullptr ) {
                        cout << "That game doesn't exist." << endl;
                    } else {
                        cout << "Not looking for another player." << endl;
                    }
                    return ERR_ALIAS_FAIL;
                }
                if ( game->getPassword().size() > 0 && game->getPassword() != password ) {
                    password_fail = true;
                    cout << "Wrong password" << endl;
                    return ERR_PASS_FAIL;
                }
                if ( game->getPlayer(name) != nullptr ) {
                    password_fail = true;
                    cout << "That player already exists." << endl;
                    return ERR_PASS_FAIL;
                }

                vector<Player*> modPlist;
                modPlist = game->getPlayerList();
                Player *pl = new Player(name);
                pl->setConnection(client);
                modPlist[game->expectedPlayerNum()] = pl;
                game->setPlayerList(modPlist);

                game->getSquare(7,7)->setOwner(pl);


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
                    GameFileManager *gfm = game->getGameLoader();
                    if ( gfm == nullptr) {

                        cout << "There is no game loader" << endl;
                    } else {

                    }
                    for ( size_t i=0; i<game->getPlayerList().size();i++ ) {
                        if ( game->getPlayerList()[i] == nullptr) {
                            cout << i << " is null " << endl;
                        }
                    }
                    string file = "";
                    try {
                        file = game->getGameLoader()->configureMultiplayerGame(game);
                        //file = game->getGameLoader()->toGameFile();
                    } catch ( exception e ) {
                        //cout << e.what();
                    }

                    ret += "\n" + file;
                }

                return ret;

          } else if (fl.at(0) == GAME) {
                if ( fl.size() < 4) {
                    bad_request = true;
                    cout << "First line too short" << endl;
                    return ERR_BAD_REQUEST;
                }
                Game *game = getGameById(fl.at(1));
                Player *player;
                if ( game == nullptr || (player = game->getPlayer(fl.at(3))) == nullptr || game->expectedPlayerNum() > -1) {
                    if ( game == nullptr ) {
                        cout << "No game found for that ID." << endl;
                    } else if (player == nullptr) {
                        cout << "No player found for that name." << endl;
                    } else {
                        cout << "Still waiting for at least one playe to join the game. Try again later" << endl;
                    }
                    bad_request = true;
                    return ERR_BAD_REQUEST;
                }

                clients = game->getPlayerList();
                clients_affected = clients;

                string ret = game->getId() + "\n";

                for ( size_t i=1; i<command.size(); i++ ) {
                    ret += command[i];
                    vector<string> line;
                    line = split(command[i],' ');
                    if ( line.size() == 0) {
                        continue;
                    }
                    if ( line.size() < 2) {
                        bad_request = true;
                        ret +=  ERR_BAD_REQUEST + "\n";
                        continue;
                    }


                    if ( line[0] == "get" ) {
                        if (line[1] == "gamefile") {
                         ret += game->getGameLoader()->toGameFile() + "\n";
                        } else if (line[1] == "dragon" ) {
                            ret += player->getName() + " " + "dragon " + "1" + "\n";
                        } else if ( line.size() == 3) {
                            //build an addition
                        } else {
                            //adding a square
                        }
                    }

                    return ret;

                }



          }
    }

    return "";

}

vector<QTcpSocket*> Control::getAffectedSockets(QTcpSocket *main_client) {
    vector<QTcpSocket*> ret;
    bool main_is_player = false;
    for ( size_t i=0; i<clients_affected.size();i++ ) {
        cout << "Client affected: " << clients_affected[i]->getName() << endl;
        if ( clients_affected.at(i)->getConnection() == main_client ) {
            main_is_player = true;
        }
        ret.push_back(clients_affected.at(i)->getConnection());
    }
    if ( !main_is_player) {
        ret.push_back(main_client);
    }
    cout << ret.size() << " connections affected " << endl;
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
