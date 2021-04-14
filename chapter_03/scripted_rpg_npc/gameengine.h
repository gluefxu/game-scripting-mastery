#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>

class GameEngine : public QWidget
{
    Q_OBJECT

public:
    GameEngine(QWidget *parent = nullptr);
    ~GameEngine();
    void run(); // run game engine

protected:
    void paintEvent(QPaintEvent *event) override; // paint buffer on the widgit
    void keyPressEvent(QKeyEvent *event) override; // handle key event

private:
    void loadScript(QString fileName); // load .cbl script file
    void runScript(); // run a line of script
    QString getCommand(); // get command
    QString getStringParam(); // get "string param" after command
    int getIntParam(); // get int param after command/string param

    void updateGame(); // update game data
    void renderGame(); // render everthing to the buffer

    // commands
    void printString(QString message); // print string to the console
    void printString(QString message, int times); // print string for several times
    void newLine(); // insert a new line
    void waitForKeyPress(); // ###

    void drawBitmap(QString image); // draw image to the buffer
    void playSound(QString sound); // play sound
    void pause(int time); // stop for a few milliseconds
    void foldCloseEffectX(); // black filter
    void foldCloseEffectY(); // black filter
    void exit(); // ###

    void print(QString message, bool newLine = false);
    void println(QString message);
    bool isCode(); // is current line code statement
    void drawGame();
    QImage createMastedImage(QString fileName, QRgb maskColor=QColor(255, 0, 255).rgb());
    void setupImages();

    void restartScript();
    void showTextBox(QString message);
    void hideTextBox();

    void quitGame();

    QStringList scriptList; // script file
    int scriptLineIndex; // index of the current script line
    QString scriptLine; // current script line
    int lineCharIndex; // character index in a line

    QImage canvasImage; // image buffer
    QImage backgroundImage;
    QImage textboxImage;
    QImage characterImage;
    QList<QImage> characterImageList;
    bool isExit;

    QString textBoxMessage;
    bool isTextBoxActive;
};
#endif // GAMEENGINE_H
