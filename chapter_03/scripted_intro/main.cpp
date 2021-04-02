#include "gameengine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameEngine w;
    w.show();
    return a.exec();
}
