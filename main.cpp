#include "roadservice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoadService w;
    w.show();

    return a.exec();
}
