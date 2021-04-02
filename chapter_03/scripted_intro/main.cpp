#include "gameengine.h"

#include <QApplication>
//#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameEngine w;
    w.show();

//    QMediaPlayer *player = new QMediaPlayer;
////    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
//    player->setMedia(QUrl::fromLocalFile("D:/title.wav"));
//    player->setVolume(20);
//    player->play();

    return a.exec();
}
