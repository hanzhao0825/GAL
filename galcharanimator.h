#ifndef GALCHARANIMATOR_H
#define GALCHARANIMATOR_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <map>
#include <cmath>
using namespace std;

class GALCharAnimator
{
public:
    GALCharAnimator();
    ~GALCharAnimator();
    void update();


    map<QString, int> charBase;
    map<QString, double> charScale;
    map<QString, QString> type;
    map<QString, int> duration, curDuration;
    map<QString, int> jumpLevel, jumpTimes;
    map<QString, int> curY;
};

#endif // GALCHARANIMATOR_H
