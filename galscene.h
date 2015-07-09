#ifndef GALSCENE_H
#define GALSCENE_H

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QSoundEffect>
#include <QApplication>
#include <QDirIterator>
#include <QResource>
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
#include "galskipper.h"
#include "galsceneshaker.h"
#include "galcharloadermanager.h"
#include "galvoice.h"

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
    void loadFrom(QString fname, int lineNum);
    void update();
    QStringList getAnotherLine();
    void nextActions();

private:
    GALStatus galStatus;
    GALTextBoard galTextBoard;
    GALBGM galBGM;
    GALVoice galVoice;
    GALBottomBar galBottomBar;
    GALDataManager galDataManager;
    GALScenePainter galScenePainter;
    GALSelect galSelect;
    GALSkipper galSkipper;
    GALSceneShaker galSceneShaker;
    GALCharLoaderManager galCharLoaderManager;

    map<QString, int> charPos;
    QFile file;
    QSound *voice;
    QString curPath;
    QString state;
    bool MUSTWAIT;
    int frameCnt;
};

#endif // GALSCENE_H
