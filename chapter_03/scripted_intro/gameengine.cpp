#include "gameengine.h"
#include <iostream>
#include <QFile>
#include <QMediaPlayer>

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent)
{
    script = QStringList();
    charIndex = 0;
}

GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
    println("# GameEngine");
    loadScript(":/scripts/demo.cbl"); // put file in the shadow build root directory
    runScript();
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
    println("# **************** runScript ****************");
    for (int i = 0; i < script.size(); ++i) {
        charIndex = 0;
        line = script.at(i);

        QString command = getCommand();

        if (command == "PrintString") {
            QString stringParam = getStringParam();
            println(stringParam);
        } else if (command == "PrintStringLoop") {
            QString stringParam = getStringParam();
            int intParam = getIntParam();
            for (int j = 0; j < intParam; ++j) {
                println(stringParam);
            }
        } else if (command == "Newline") {
            println("");
        } else if (command == "WaitForKeyPress") {
            println("!!WaitForKeyPress");
        } else {
            println("!!Error Command: " + command);
        }

        playSound("sound/title.wav");
    }
    println("# **************** runScript end ******************");
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


void GameEngine::playSound(QString fileName)
{
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/" + fileName));
    player->setVolume(5);
    player->play();
}

void GameEngine::print(QString message, bool newLine)
{
    if (newLine) {
        std::cout << message.toStdString() << std::endl;
    } else {
        std::cout << message.toStdString();
    }
}

void GameEngine::println(QString message)
{
    print(message, true);
}
