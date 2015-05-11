#ifndef GALSCENESHAKER_H
#define GALSCENESHAKER_H

#include <QTime>

class GALSceneShaker
{
public:
    GALSceneShaker();
    ~GALSceneShaker();
    int maxX, maxY;
    int curX, curY;
    int duration;
    void update(bool &MUSTWAIT);
};

#endif // GALSCENESHAKER_H
