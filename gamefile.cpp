#include "gamefile.h"
#include "gamemodel.h"
#include "player.h"
#include "square.h"
#include "utils.h"
#include <iostream>

std::string GameFileManager::toGameFile() {

    std::string output = "";

    //Add header file
    output += "RoadRaceDoc " + game->getId() + "\n";

    //Add alias/password line
    output += "alias " + game->getAlias() + " password " + game->getPassword() + "\n";

    //Add round number
     output += "round " + std::to_string(game->getRoundNum()) + "\n";

    //Add player list
    output += "players ";

    for ( size_t i = 0; i<game->getPlayerList().size(); i++ ) {
        output += game->getPlayerList().at(i)->getName() + " ";
    }

    output += "\n";

    //Add player info
    for ( size_t i = 0; i<game->getPlayerList().size(); i++ ) {
        Player *p = game->getPlayerList().at(i);
        output += "info " + p->getName() + " resources ";
        output += "Go," + std::to_string(p->getGold()) + " ";
        output += "Wo," + std::to_string(p->getWood()) + " ";
        output += "St," + std::to_string(p->getStone()) + " ";
        output += "Wa," +std::to_string(p->getWater()) + " ";
        output += "status ";
        output += "score," + std::to_string(p->getScore()) + " ";
        output += "startTime," + std::to_string(p->getStartTime());
        output += "\n";
    }

    //Add board head
    output += "board " + std::to_string(game->getWidth()) + "," + std::to_string(game->getHeight()) + "\n";

    //Add board contents
    for ( size_t i=0; i<game->getSquares().size(); i++ ) {
        for ( size_t j=0; j<game->getSquares().at(i).size(); j++ ) {
            Square *s = game->getSquare(i,j);
               std::string type = s->getType(),
                       addition = s->getAddition(),
                       owner = s->getOwner() == NULL ? "" : s->getOwner()->getName();
              output += type + "," + addition + "," + owner + " ";
        }
        output += "\n";
    }

    //Add endfile
    output += "EndRoadRaceDoc";

    return output;

}

GameFileManager::GameFileManager ( Game *game_, std::vector<std::string> contents ) {

    game = game_;
    // /Users/jbrazeal/Desktop/School/2015-2016/Spring/CpS_209/TPfork/roadrace/road_race/gamefile.rr

    std::stringstream stream;

    for ( size_t i=0; i<contents.size();i++) {
        stream << contents[i] << std::endl;
    }

    const std::string fileIdentifier = "RoadRaceDoc",
            gameAlias = "alias",
            gamePassword = "password",
            roundNum = "round",
            playerList = "players",
            playerInfo = "info",
            playerResourceList = "resources",
            playerStatus = "status",
            boardStart = "board",
            endFile = "EndRoadRaceDoc";


    std::string identifier;
    std::string command;

    stream >> identifier;

    while ( stream ) {

        if (identifier == fileIdentifier) {
            stream >> command;
            game->setId(command);
        } else if ( identifier == gameAlias) {
            stream >> command;
            game->setAlias(command);
        } else if ( identifier == gamePassword ) {
            stream >> command;
            game->setPassword(command);
        } else if ( identifier == roundNum) {
            stream >> command;
            game->setRoundNum(stoi(command));
        } else if ( identifier == playerList ) {
            stream >> command;
            std::vector<std::string> names;
            std::vector<Player*> players;
            vector<std::string> defaultColorList = {"red","green","yellow","blue"};

            names = split(command,',');
            for (size_t i=0; i<names.size(); i++) {
                if (names[i].size() == 0) {
                    continue;
                }
                players.push_back(new Player(names[i]));

                players.at(i)->setColor(defaultColorList.at(i));

            }
            game->setPlayerList(players);
            //hacky. TODO: figure out real cur player for multi-player networking!
            game->setCurPlayer(players.at(0));
        } else if ( identifier == playerInfo) {
            stream >> command;
            Player * pl = game->getPlayer(command);
            if ( pl == NULL ) {
                std::cerr << "Player '" + command + "' not previously listed in game file." << std::endl;
                return;
            }
            stream >> identifier;
            if ( identifier == playerResourceList) {
                stream >> command;
                while ( command != playerStatus) {
                    std::vector<std::string> resource;
                    const std::string water = "Wa", gold = "Go", wood = "Wo", stone = "St";
                    resource = split(command, ',');

                    std::string type = resource[0];
                    int quantity = std::stoi(resource[1]);

                    if ( type == water ) {
                        pl->setWater(quantity);
                    } else  if ( type == gold ) {
                        pl->setGold(quantity);
                    } else  if ( type == wood ) {
                        pl->setWood(quantity);
                    } else  if ( type == stone ) {
                        pl->setStone(quantity);
                    }

                    stream >> command;
                }
                if ( command == playerStatus ) {
                    const int numStatusArgs = 2;
                    const std::string score = "score", startTime = "start_time";
                    for (int i=0; i<numStatusArgs; i++ ) {
                        stream >> command;
                        std::vector<std::string> statusItem;
                        statusItem = split(command,',');
                        std::string statusType = statusItem[0];
                        int statusQuantity = std::stoi(statusItem[1]);
                        if (statusType == score ) {
                            pl->setScore(statusQuantity);
                        } else if (statusType == startTime) {
                            pl->setStartTime(statusQuantity);
                        }
                    }
                }
            }
        } else if ( identifier == boardStart ) {
            stream >> command;
            std::vector<std::string> dim;
            dim = split(command,',');
            int x = stoi(dim[0]),
                    y = stoi(dim[1]);
            game->setHeight(x);
            game->setWidth(y);

            std::vector<std::vector<Square*>> squares;

            for ( int i=0; i<x; i++ ) {
                squares.push_back(vector<Square*>());
                for ( int j = 0; j<y; j++ ) {
                   stream >> command;
                   std::vector<std::string> square;
                   square = split(command,',');

                   std:string terrain = square[0],

                           addition = square[1],
                           ownerName = square[2];


                         if(ownerName == "No"){
                             Player *noOne = nullptr;
                              squares[i].push_back( new Square(terrain,addition,noOne));
                         }
                 else{
                   Player *owner = game->getPlayer(ownerName);
                   squares[i].push_back( new Square(terrain,addition,owner));
                    }
                 }
            }
            game->setSquares(squares);
        } else if ( identifier == endFile ) {
            break;
        }

       stream >> identifier;
    }
}

GameFileManager *GameFileManager::fromFile(Game *game_, std::string fileName ) {

    if ( fileName.size() == 0) {
        fileName = "gamefile.rr";
    }
    std::string line;

    std::vector<std::string> contents;
    std::ifstream gamefile (fileName);
    if (gamefile.is_open())
    {
      while ( std::getline (gamefile,line) )
      {
        contents.push_back(line);
      }
      gamefile.close();
    }

    else {
        std::cerr << "Game file '" << fileName << " does not exist.";
    }

    return new GameFileManager(game_, contents);
}

void GameFileManager::claimSquare(Player *player) {
    std::vector<int> square_coords = game->getLevelManager()->getPlayerCoords(player);
    Square * square = game->getSquare(square_coords[0], square_coords[1]);
    if (square) {
        square->setOwner(player);
    }
}


//Only call at the VERY beginning of a game
//Note: players are not set
std::string GameFileManager::configureMultiplayerGame(Game *game_) {
    std::string ret = "RoadRaceDoc " + game_->getId() + "\n";
    ret += "alias " + game_->getAlias() + " password " + game_->getPassword() + "\n";
    ret += "round " + to_string(game_->getLevelManager()->whatLevel()) + "\n";
    ret += "players " + game_->gameFilePlayerList() + "\n";
    ret += game_->gameFileResourceList();
    ret += "board " + game_->getLevelManager()->getDim() + "\n";

    std::vector<std::string> board = game_->getLevelManager()->getLevel();

    for ( size_t i=0; i<board.size(); i++ ) {
        ret += board.at(i) + "\n";
    }

    ret += "EndRoadRaceDoc";

    //store for later: will be overwritten at the next step
    //by phantom "unknown1" players, which we don't want hanging around.
    //NOT A MEMORY LEAK
    vector<Player*> plist = game_->getPlayerList();
    game_->setPlayerList(vector<Player*>());

    //Completely restart the train
    game_->setGameLoader(new GameFileManager(game_,split(ret,'\n')));

    for ( size_t i=0; i<game_->getPlayerList().size(); i++ ) {
        delete game_->getPlayerList()[i];
        game_->getPlayerList()[i] = plist[i];
    }

    return ret;


}
