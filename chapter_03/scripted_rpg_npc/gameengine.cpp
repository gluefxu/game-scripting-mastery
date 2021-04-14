#include "gameengine.h"
#include <iostream>
#include <QFile>
#include <QMediaPlayer>
#include <QPainter>
#include <QTime>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QEvent>
#include <QTimer>

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent)
{
    scriptLineIndex = 0;
    scriptList = QStringList();
    lineCharIndex = 0;
    isExit = false;
    setupImages();

//    setAttribute(Qt::WA_QuitOnClose);
    textBoxMessage = "";
    isTextBoxActive = false;
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

    drawGame();

    for (int i = 0; i < scriptList.size(); ++i) {
        if (isExit) {
            println("run exit end");
//            this->close();
//            qApp->quit();
            break;
        }
        lineCharIndex = 0;
        scriptLine = scriptList.at(i);
        if (!isCode()) {
            continue;
        }
        runScript();
    }
    println("run end loop");
//    update();
    qApp->quit();
}

bool GameEngine::isCode()
{
    QChar c = scriptLine.at(0);
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
        scriptList << line;
    }
}

void GameEngine::runScript()
{
//    print(scriptLine);
//    println("# **************** runScript ****************");

    QString command = getCommand();
    QString stringParam = "";
    int intParam = 0;

    if (command == "PrintString") {
        stringParam = getStringParam();
        println(stringParam);
    } else if (command == "PrintStringLoop") {
        stringParam = getStringParam();
        intParam = getIntParam();
        for (int j = 0; j < intParam; ++j) {
            println(stringParam);
        }
    } else if (command == "Newline") {
        println("");
    } else if (command == "WaitForKeyPress") {
        println("!!WaitForKeyPress");

    } else if (command == "DrawBitmap") {
        stringParam = getStringParam();
        drawBitmap(stringParam);
        update();
    } else if (command == "PlaySound") {
        stringParam = getStringParam();
        playSound(stringParam);
    } else if (command == "Pause") {
        intParam = getIntParam();
        pause(intParam);
    } else if (command == "FoldCloseEffectY") {
        foldCloseEffectY();
    } else if (command == "FoldCloseEffectX") {
        foldCloseEffectX();
    } else if (command == "ShowTextBox") {
        stringParam = getStringParam();
//        println(stringParam);
        showTextBox(stringParam);
        update();
    } else if (command == "HideTextBox") {
        hideTextBox();
        update();
    } else {
//        println("!!Error Command: " + command);
    }

//    }
//    println("# **************** runScript end ******************");
}

QString GameEngine::getCommand()
{
    QString command = "";
    for (int i = lineCharIndex; i < scriptLine.size() ; i++ ) {
        lineCharIndex++;
        QChar c = scriptLine.at(i);
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
    lineCharIndex++;
    for (int i = lineCharIndex; i < scriptLine.size() ; i++ ) {
        lineCharIndex++;
        QChar c = scriptLine.at(i);
        if (c == "\"") {
            break;
        }
        stringParam.push_back(c);
    }
    lineCharIndex++;

    return stringParam;
}

int GameEngine::getIntParam()
{
    QString intParam = "";
    for (int i = lineCharIndex; i < scriptLine.size() ; i++ ) {
        lineCharIndex++;
        QChar c = scriptLine.at(i);
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
    canvasImage.load(":/" + image);
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
    QPainter painter(&canvasImage);
    int width = canvasImage.width();
    int height = canvasImage.height();
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
    QPainter painter(&canvasImage);
    int width = canvasImage.width();
    int height = canvasImage.height();
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
    println("--- pause start");
    QTime dieTime = QTime::currentTime().addMSecs( time );
    while( QTime::currentTime() < dieTime )
    {
        if (isExit) {
            println("pause end");
//            qApp->quit();
//            QEvent *e = new QEvent(QEvent::Close);
//            QCoreApplication::sendEvent(this, e);
            break;
        }
        QCoreApplication::processEvents( QEventLoop::AllEvents, 1000 );
    }
    println("--- pause end");
}

void GameEngine::paintEvent(QPaintEvent *)
{
    drawGame();

    QRectF source(0.0, 0.0, 640, 480.0);
    QRectF target(0.0, 0.0, 640.0, 480.0);

    QPainter painter(this);
    painter.drawImage(target, canvasImage, source);
}

void GameEngine::keyPressEvent(QKeyEvent *event)
{
//    event->key() == Qt::Key_Escape
    switch (event->key()) {
    case Qt::Key_Escape:
        println("!!!Quit");
        isExit = true;
//        this->close();
        qApp->quit();
//        QTimer::singleShot(2000, qApp, SLOT(quit));
        break;
    default:
        break;
    }
}

void GameEngine::drawGame()
{
    QRect backgroundSource(0, 0, 640, 480);
    QRect backgroundTarget(0, 0, 640, 480);

    QPainter painter(&canvasImage);
    painter.drawImage(backgroundTarget, backgroundImage, backgroundSource);

    QRect characterSource(0, 0, 48, 64);
    QRect characterTarget(100, 100, 48, 64);

    painter.drawImage(characterTarget, characterImage, characterSource);

    if (isTextBoxActive) {
        QRect textboxSource(0, 0, 588, 94);
        QRect textboxTarget(26, 360, 588, 94);
        painter.drawImage(textboxTarget, textboxImage, textboxSource);

        QRect textRect = QRect(26 + 20, 360 + 20, 588 - 40, 94 - 40);

        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 16));
        painter.drawText(textRect, Qt::TextWordWrap, textBoxMessage);
    }
}

QImage GameEngine::createMastedImage(QString fileName, QRgb maskColor)
{
    QImage colorImage = QImage(fileName);
    QImage alphaImage = colorImage.createMaskFromColor(maskColor, Qt::MaskOutColor);
    colorImage.setAlphaChannel(alphaImage);
    return colorImage;
}

void GameEngine::setupImages()
{
    canvasImage = QImage(640, 480, QImage::Format_RGB32);
    backgroundImage = QImage(":/gfx/castle_bg.bmp");

    QRgb maskColor = QColor(255, 0, 255).rgb();

    textboxImage = createMastedImage(":/gfx/textbox.bmp");

    characterImageList = QList<QImage>();
    QImage characterImageLeft0 = createMastedImage(":/gfx/character/left_0.bmp");
    QImage characterImageLeft1 = createMastedImage(":/gfx/character/left_1.bmp");
    QImage characterImageRight0 = createMastedImage(":/gfx/character/right.bmp");
    QImage characterImageRight1 = createMastedImage(":/gfx/character/left_0.bmp");
    QImage characterImageUp0 = createMastedImage(":/gfx/character/left_0.bmp");
    QImage characterImageUp1 = createMastedImage(":/gfx/character/left_0.bmp");
    QImage characterImageDown0 = createMastedImage(":/gfx/character/left_0.bmp");
    QImage characterImageDown1 = createMastedImage(":/gfx/character/left_0.bmp");


    QStringList images = { "left_0", "left_1", "right_0", "right_1", "up_0", "up_1", "down_0", "down_1" };
    for (int i = 0; i < images.size(); ++i) {
        QString imageName = images.at(i);
        QImage tmpImage = createMastedImage(":/gfx/character/" + imageName + ".bmp");
        characterImageList.append(tmpImage);
    }

    characterImage = characterImageList.at(0);
}

void GameEngine::restartScript()
{
    scriptLineIndex = 0;
    scriptLine = scriptList[0];
}

void GameEngine::showTextBox(QString message)
{
    isTextBoxActive = true;
    textBoxMessage = message;
}

void GameEngine::hideTextBox()
{
    isTextBoxActive = false;
    textBoxMessage = "";
}

void GameEngine::quitGame()
{
    qApp->quit();
}
