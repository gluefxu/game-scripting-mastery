#include "gameengine.h"
#include <iostream>
#include <QFile>
#include <QMediaPlayer>
#include <QPainter>
#include <QTime>
#include <QCoreApplication>
#include <QDebug>

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent)
{
    script = QStringList();
    charIndex = 0;
    canvas = QImage(640, 480, QImage::Format_RGB32);
}

GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
    resize(640, 480);
    println("# GameEngine");
    loadScript(":/scripts/npc.cbl"); // put file in the shadow build root directory
//    runScript();

    qDebug() << "hello";

    for (int i = 0; i < script.size(); ++i) {
        charIndex = 0;
        line = script.at(i);
        if (!isCode()) {
            continue;
        }
        runScript();
    }
    update();
}

bool GameEngine::isCode()
{
    QChar c = line.at(0);
    return !(c == "/" || c == " " || c == "\n");
}

void GameEngine::loadScript(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        println("# File Open Error");
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        script << line;
    }
}

void GameEngine::runScript()
{
    print(line);
//    qDebug() << line;
//    println("# **************** runScript ****************");
//    for (int i = 0; i < script.size(); ++i) {
//        charIndex = 0;
//        line = script.at(i);

    QString command = getCommand();
    QString stringParam = "";
    int intParam = 0;

//    if (command == "PrintString") {
//        stringParam = getStringParam();
//        println(stringParam);
//    } else if (command == "PrintStringLoop") {
//        stringParam = getStringParam();
//        intParam = getIntParam();
//        for (int j = 0; j < intParam; ++j) {
//            println(stringParam);
//        }
//    } else if (command == "Newline") {
//        println("");
//    } else if (command == "WaitForKeyPress") {
//        println("!!WaitForKeyPress");

//    } else if (command == "DrawBitmap") {
//        stringParam = getStringParam();
//        drawBitmap(stringParam);
//        update();
//    } else if (command == "PlaySound") {
//        stringParam = getStringParam();
//        playSound(stringParam);
//    } else if (command == "Pause") {
//        intParam = getIntParam();
//        pause(intParam);
//    } else if (command == "FoldCloseEffectY") {
//        foldCloseEffectY();
//    } else if (command == "FoldCloseEffectX") {
//        foldCloseEffectX();
//    } else {
//        println("!!Error Command: " + command);
//    }

//    }
//    println("# **************** runScript end ******************");
}

QString GameEngine::getCommand()
{
    QString command = "";
    for (int i = charIndex; i < line.size() ; i++ ) {
        charIndex++;
        QChar c = line.at(i);
        if (c == " " || c == "\n") {
            break;
        }
        command.push_back(c);
    }
    return command;
}

QString GameEngine::getStringParam()
{
    QString stringParam = "";
    charIndex++;
    for (int i = charIndex; i < line.size() ; i++ ) {
        charIndex++;
        QChar c = line.at(i);
        if (c == "\"") {
            break;
        }
        stringParam.push_back(c);
    }
    charIndex++;

    return stringParam;
}

int GameEngine::getIntParam()
{
    QString intParam = "";
    for (int i = charIndex; i < line.size() ; i++ ) {
        charIndex++;
        QChar c = line.at(i);
        if (c == " " || c == "\n") {
            break;
        }
        intParam.push_back(c);
    }
    int intParamValue = intParam.toInt();
    return intParamValue;
}

void GameEngine::drawBitmap(QString image)
{
    canvas.load(":/" + image);
}

void GameEngine::playSound(QString sound)
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/" + sound));
    player->setVolume(5);
    player->play();
}

void GameEngine::foldCloseEffectX()
{
    int frameStep = 10;
    QPainter painter(&canvas);
    int width = canvas.width();
    int height = canvas.height();
    for (int i = 0; i < width / 2; ++i) {
        painter.drawLine(i, 0, i, height);
        painter.drawLine(width - i -1, 0, width - i -1, height);
        update();
        pause(frameStep);
    }
}

void GameEngine::foldCloseEffectY()
{
//    int duration = 1000;
//    int fps = 60;
    int frameStep = 10;
    QPainter painter(&canvas);
    int width = canvas.width();
    int height = canvas.height();
    for (int i = 0; i < height / 2; ++i) {
        painter.drawLine(0, i, width, i);
        painter.drawLine(0, height - i -1, width, height - i -1);
        update();
        pause(frameStep);
    }
}



void GameEngine::print(QString message, bool newLine)
{
    if (newLine) {
        std::cout << message.toStdString() << std::endl;
    } else {
        std::cout << message.toStdString();
    }
    std::cout.flush();
}

void GameEngine::println(QString message)
{
    print(message, true);
}

void GameEngine::pause(int time)
{
    QTime dieTime = QTime::currentTime().addMSecs( time );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void GameEngine::paintEvent(QPaintEvent *)
{
    QRectF source(0.0, 0.0, 640, 480.0);
    QRectF target(0.0, 0.0, 640.0, 480.0);

    QPainter painter(this);
    painter.drawImage(target, canvas, source);


}
