#ifndef GALSTATUS_H
#define GALSTATUS_H

#include <map>
#include <QPainter>
#include <QDebug>
#include <QSound>
#include <vector>
using namespace std;
class GALStatus
{
public:
    GALStatus();
    ~GALStatus();

    map<QString, pair<QString, int> > curChar; //name, <gesture, pos>
    QString curScene;
    QString curBGM;
    QString fname;
    int lineNum;

};

#endif // GALSTATUS_H
