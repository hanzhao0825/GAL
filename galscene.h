#ifndef GALSCENE_H
#define GALSCENE_H

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QSoundEffect>
#include <QApplication>
#include <QSound>
#include <vector>
#include <map>
#include <fstream>
#include "galtextboard.h"
#include "galstatus.h"
#include "galbgm.h"
#include "galbottombar.h"
#include "galdatamanager.h"
#include "galscenepainter.h"
#include "galselect.h"

using namespace std;
class GALScene
{
public:
    GALScene();
    ~GALScene();
    void paint(QPainter &painter);
    void mousePress(QMouseEvent *e);
    void mouseMove(QMouseEvent *e);
    void keyPress(QKeyEvent *e);
    void jumpToScript(QString fname);
    void jumpToScript(QString fname, int lineNum);

private:
    GALStatus galStatus;
    GALTextBoard galTextBoard;
    GALBGM galBGM;
    GALBottomBar galBottomBar;
    GALDataManager galDataManager;
    GALScenePainter galScenePainter;
    GALSelect galSelect;

    map<QString, int> charPos;
    map<QString, QImage> charImg;
    QImage scene;
    QFile file;
    QStringList getAnotherLine();
    bool MUSTWAIT;
    void nextActions();
    QSound *voice;
    QString curPath;
    void saveTo(QString fname);
    void loadFrom(QString fname);

    QString state;

};

#endif // GALSCENE_H
