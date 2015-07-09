#ifndef GALSTATUS_H
#define GALSTATUS_H

#include <map>
#include <QPainter>
#include <QDebug>
#include <QSound>
#include <vector>
#include <QFile>
#include <QDateTime>
#include "galcharanimator.h"
#include "galscenechanger.h"
#include "galcharloadermanager.h"

using namespace std;
class GALStatus
{
public:
    GALStatus();
    ~GALStatus();
    void init();
    void saveTo(QString fname);
    void loadFrom(QString fname, GALCharLoaderManager *galCharloaderManager);
    void update();

    GALCharAnimator galCharAnimator;
    GALSceneChanger galSceneChanger;
    QString fname;
    map<QString, pair<map<QString, QString>, int> > curChar; //name, <gesture, position>
    QString curScene, curMask, curChanger;
    QString curBGM;
    QString curDate;
    int lineNum;
    QString lastWords;
    map<QString, int> jump;

    map<QString, map<pair<QString, QString>, QPixmap> > charImg;
    map<QString, map<pair<QString, QString>, pair<int, int> > > charPos;
    QPixmap scene, mask, changer;

    QPixmap cap;

    QString nextScene;

};

#endif // GALSTATUS_H
