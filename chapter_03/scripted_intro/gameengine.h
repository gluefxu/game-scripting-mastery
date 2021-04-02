#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>

class GameEngine : public QWidget
{
    Q_OBJECT

public:
    GameEngine(QWidget *parent = nullptr);
    ~GameEngine();

    void loadScript(QString fileName);
    void runScript();
    QString getCommand();
    QString getStringParam();
    int getIntParam();

    void print(QString message, bool newLine = false);
    void println(QString message);

    QStringList script;
    int charIndex;
    QString line;
};
#endif // GAMEENGINE_H
