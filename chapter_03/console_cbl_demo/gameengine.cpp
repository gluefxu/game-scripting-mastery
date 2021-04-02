#include "gameengine.h"
#include <iostream>
#include <QFile>

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent)
{
    script = QStringList();
    println("# GameEngine");
    loadScript("demo.cbl"); // put file in the shadow build root directory
    runScript();
}

GameEngine::~GameEngine()
{
}

void GameEngine::loadScript(QString fileName)
{
    println("# loadScript");
    println(fileName);

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
    println("# runScript");
    for (int i = 0; i < script.size(); ++i) {
        QString line = script.at(i);
        print(line);
    }
    println("\n# runScript end");
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
