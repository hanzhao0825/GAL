#ifndef GALSKIPPER_H
#define GALSKIPPER_H

#include <QFile>
#include <QDebug>
#include <QDir>
#include <map>
using namespace std;
class GALSkipper
{
public:
    GALSkipper();
    ~GALSkipper();
    bool skip;
    map<QString, int> lines;
    void save();
};

#endif // GALSKIPPER_H
