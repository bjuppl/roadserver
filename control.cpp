#include "control.h"
#include "utils.h"

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


Game *Control::getGameByAlias(string alias){
    for ( size_t i=0; i<gameList.size(); i++ ) {
        if ( gameList[i]->getAlias() == alias ) {
            return gameList[i];
        }
    }
    return nullptr;
}

string Control::clientCommandResponse(vector<string> command) {

    bool game_init_error = false,
            alias_fail = false,
            password_fail = false;
    const string ERR_GAME_INIT = "game_init_error",
            ERR_ALIAS_FAIL = "alias_fail",
            ERR_PASS_FAIL = "password_fail";

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
        for ( size_t i=1; i<player_cnt; i++ ) {
            plist.push_back(nullptr);
        }

        game->setPlayerList(plist);

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
          } else if (fl.at(0) == GAME) {
                const string ALIAS = "alias",
                        PASSWORD = "password";
                string alias = "",
                        password = "";

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
                    }
                }

                Game *game = getGameByAlias(alias);

                // Failure to join: either game does not exist, or is not waiting for new members.
                if ( game == nullptr || game->expectedPlayerNum() == -1 ) {
                    alias_fail = true;
                    return ERR_ALIAS_FAIL;
                }
                if ( game->getPassword().size() > 0 && game->getPassword() != password ) {

                    return ERR_PASS_FAIL;
                }



          }
    }

    return "";

}

Game *Control::launch() {

    //figure out an ID
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
