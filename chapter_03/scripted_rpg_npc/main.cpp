#include "gameengine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameEngine g;
    g.show();
    g.run();


    return a.exec();
}
