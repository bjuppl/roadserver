#ifndef ROADSERVICE_H
#define ROADSERVICE_H

#include <QMainWindow>
#include <QTcpServer>

namespace Ui {
class RoadService;
}

class RoadService : public QMainWindow
{
    Q_OBJECT

private:
    Ui::RoadService *ui;

public:
    explicit RoadService(QWidget *parent = 0);
    void addToLog( QString str );
    ~RoadService();

private slots:
    void clientConnected();
    void dataReceived();
    void clientDisconnected();

private:

    QTcpServer *server;
    int connectCount;
signals:
    void actionReceived();
};

#endif // ROADSERVICE_H
