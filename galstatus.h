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

using namespace std;
class GALStatus
{
public:
    GALStatus();
    ~GALStatus();
    void init();
    void clear();
    void saveTo(QString fname);
    void loadFrom(QString fname);
    void update();

    GALCharAnimator galCharAnimator;
    QString fname;
    map<QString, pair<map<QString, QString>, int> > curChar; //name, <gesture, position>
    QString curScene, curMask;
    QString curBGM;
    QString curDate;
    int lineNum;
    QString lastWords;
    map<QString, int> jump;

    map<QString, QImage> charImg;
    QImage scene, mask;
};

#endif // GALSTATUS_H
