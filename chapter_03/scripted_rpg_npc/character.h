#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QImage>

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(QObject *parent = nullptr);
    explicit Character(int px, int py);

    void setupImages();
    QImage currentImage();



    int direction; // 0, 1, 2, 3 : left, right, up, down
    int posX;
    int posY;
    int moveX;
    int moveY;
    int animationFrame; // 0, 1: left_0.bmp, left_1.bmp
    QList<QImage> imageList;
    int imageWidth;
    int imageHeight;

public slots:
    void updateAnimation();
//signals:

//private:


};

#endif // CHARACTER_H
