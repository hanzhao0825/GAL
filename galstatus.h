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
    void clear();
    void saveTo(QString fname);
    void loadFrom(QString fname);
    void update();

    GALCharAnimator galCharAnimator;
    QString fname;
    map<QString, pair<map<QString, QString>, int> > curChar; //name, <gesture, position>
    QString curScene;
    QString curBGM;
    QString curDate;
    int lineNum;
    QString lastWords;
    map<QString, int> jump;
};

#endif // GALSTATUS_H
