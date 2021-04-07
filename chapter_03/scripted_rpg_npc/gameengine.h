#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>

class GameEngine : public QWidget
{
    Q_OBJECT

public:
    GameEngine(QWidget *parent = nullptr);
    ~GameEngine();

    void run();
    void loadScript(QString fileName);
    void runScript();
    QString getCommand();
    QString getStringParam();
    int getIntParam();
    void drawBitmap(QString image);
    void playSound(QString sound);
    void pause(int time);
    void foldCloseEffectX();
    void foldCloseEffectY();


    void print(QString message, bool newLine = false);
    void println(QString message);
    void delay( int time );
    bool isCode();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QStringList script; // script file
    int charIndex; // character index in a line
    QString line; // current script line
    QImage canvas; // image buffer
    bool exit;
};
#endif // GAMEENGINE_H
