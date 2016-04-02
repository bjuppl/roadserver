#include "updater.h"

/*void Updater::removeGame(string id) {
    for ( size_t i=0; i<gameList.size(); i++ ) {
        if ( gameList[i]->getId() == id ) {
            gameList[i]->stop();
            return;
        }
    }
}
*/
void Updater::start(){
    timer->start(interval_ms);
    started_at = time.currentMSecsSinceEpoch();
    eventTime->start(30000);
}

void Updater::stop() {
    timer->stop();
    duration = time.currentMSecsSinceEpoch() - started_at;
    eventTime->stop();
}

void Updater::run() {
    duration = time.currentMSecsSinceEpoch() - started_at;
    game->update();
}

/*Updater& Updater::instance() {
    if (instance_ == NULL ) {
        instance_ = new Updater();
    }
    return *instance_;
}*/
