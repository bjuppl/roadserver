#ifndef UPDATER_H
#define UPDATER_H

#include "gamemodel.h"

class Game;

class Updater : public QObject{
    Q_OBJECT

private:
    QDateTime time;
    size_t started_at;
    size_t duration;
    QTimer *timer;
    QTimer *eventTime;
    Game *game;
    int interval_ms{1000}; //default

    //static Updater *instance_;
private slots:
    void run();
    void eventrun();
public:
    Updater(Game *game_) : game(game_){
            eventTime = new QTimer();
            timer = new QTimer();
            connect(timer,SIGNAL(timeout()),this,SLOT(run()));
            connect(eventTime,SIGNAL(timeout()),this,SLOT(eventrun()));
    }

    //static Updater &instance();

    Game* getGame () { return game; }
    void setGame( Game *g) { game = g; }
    void start();
    void stop();

    size_t getStartTime () { return started_at; }
    size_t getDuration() { return time.currentMSecsSinceEpoch() - started_at; }
    int getMs() { return interval_ms; }
    void setMs ( int ms ) { interval_ms = ms; }
    ~Updater () { delete timer; }
};

#endif // UPDATER_H
