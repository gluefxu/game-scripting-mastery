#include "gameengine.h"
#include <iostream>
#include <QFile>

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent)
{
    script = QStringList();
    charIndex = 0;

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
//    println(fileName);

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
    println("# runScript **************************");
    for (int i = 0; i < script.size(); ++i) {
        charIndex = 0;
        line = script.at(i);
//        print(line);

//        QStringList commandLine = line.split(" ");
//        QString command = commandLine.at(0);


        QString command = getCommand();

        if (command == "PrintString") {
//            print(command + ": ");
            QString stringParam = getStringParam();
            println(stringParam);
        } else if (command == "PrintStringLoop") {
//            print(command + ":\n");
            QString stringParam = getStringParam();
//            println(stringParam);
            int intParam = getIntParam();
//            println(QString::number(intParam));
            for (int j = 0; j < intParam; ++j) {
                println(stringParam);
            }
        } else if (command == "Newline") {
            println("");
        } else if (command == "WaitForKeyPress") {
            println("WaitForKeyPress");
        } else {
            println("!!Error Command: " + command);
        }
    }
    println("# runScript end ***********************");
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

//    print(command);
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
//    print(stringParam);
    return stringParam;
}

int GameEngine::getIntParam()
{
    QString intParam = "";
//    println(QString::number(charIndex));
    for (int i = charIndex; i < line.size() ; i++ ) {
        charIndex++;
        QChar c = line.at(i);
        if (c == " " || c == "\n") {
            break;
        }
        intParam.push_back(c);
    }
//    print("intParam:" + intParam);
    int intParamValue = intParam.toInt();
    return intParamValue;
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
