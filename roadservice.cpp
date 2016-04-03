#include "roadservice.h"
#include "ui_roadservice.h"
#include "listener.h"
#include "levelmanager.h"
#include <QDateTime>
#include <QTcpSocket>
#include <QMessageBox>
#include <exception>

#include "control.h"
using namespace std;

class Control;
RoadService::RoadService(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoadService)
{
    ui->setupUi(this);

    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &RoadService::clientConnected);
    if (!server->listen(QHostAddress::Any, 3141)) {
        QMessageBox::critical(this, "Uh oh", "Cannot start socket.");

        exit(1);
    }

}

void RoadService::addToLog(QString str){
    QDateTime now = QDateTime::currentDateTime();
    ui->output->append(now.toString("hh:mm:ss") + " " + str);

}

void RoadService::clientConnected(){
    QTcpSocket *sock = server->nextPendingConnection();
    connect(sock, &QTcpSocket::disconnected, this, &RoadService::clientDisconnected);
    connect(sock, &QTcpSocket::readyRead, this, &RoadService::dataReceived);
    ++connectCount;
    ui->lblConnections->setText(QString::number(connectCount));
    addToLog("Client connected.");


}

void RoadService::dataReceived() {
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    addToLog("Received data from socket ");

    //What they said
    vector<string> input;
    while (sock->canReadLine()) {
       input.push_back(sock->readLine().toStdString());
    }

    //What we say
    QString output = QString::fromStdString(Control::instance().clientCommandResponse(input, sock));

    //Who to say it to?
    for (QTcpSocket *obj : Control::instance().getAffectedSockets(sock)) {
            obj->write(output.toLocal8Bit());
    }


}

void RoadService::clientDisconnected() {
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    sock->deleteLater();
    --connectCount;
    ui->lblConnections->setText(QString::number(connectCount));
    addToLog("Client disconnected.");
}

RoadService::~RoadService()
{
    delete ui;
}
