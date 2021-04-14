#include "character.h"
#include <QTimer>

Character::Character(QObject *parent) : QObject(parent)
{

}

Character::Character(int px, int py) : posX(px), posY(py)
{
    imageList = QList<QImage>();
    direction = 0;
    moveX = 0;
    moveY = 0;
    animationFrame = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->start(500);
}


QImage Character::currentImage()
{
    int index = direction * 2 + animationFrame;
    return imageList.at(index);
}

void Character::updateAnimation()
{
    animationFrame = animationFrame == 0 ? 1 : 0;
}
