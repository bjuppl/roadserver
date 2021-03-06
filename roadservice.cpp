#include "roadservice.h"
#include "ui_roadservice.h"
#include "listener.h"
#include "levelmanager.h"
#include <QDateTime>
#include <QTcpSocket>
#include <QMessageBox>
#include <exception>
#include <iostream>

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
        QString s = sock->readLine();
        qDebug() << s;
        if ( s.size() > 0) {
            input.push_back(s.toStdString());
            addToLog( "->\t" + s + "\n");
        }
    }

    //What we say
    QString output = QString::fromStdString(Control::instance().clientCommandResponse(input, sock)) + "\n";
    //qDebug() << output;
    //Who to say it to?
    vector<QTcpSocket*> out = Control::instance().getAffectedSockets(sock);
    for (QTcpSocket *obj : out ) {
            if (obj) {
                obj->write(output.toLocal8Bit());
            }

    }

    //That's a lock!
    addToLog(output);

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
