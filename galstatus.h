#ifndef GALSTATUS_H
#define GALSTATUS_H

#include <map>
#include <QPainter>
#include <QDebug>
#include <QSound>
#include <vector>
#include <QFile>
#include <QDateTime>
using namespace std;
class GALStatus
{
public:
    GALStatus();
    ~GALStatus();
    void clear();
    void saveTo(QString fname);
    void loadFrom(QString fname);

    map<QString, pair<QString, int> > curChar; //name, <gesture, pos>
    QString curScene;
    QString curBGM;
    QString fname;
    QString curDate;
    int lineNum;
    QString lastWords;
};

#endif // GALSTATUS_H
