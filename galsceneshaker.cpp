#include "galsceneshaker.h"

GALSceneShaker::GALSceneShaker()
{
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    duration = 0;
}

GALSceneShaker::~GALSceneShaker()
{

}

void GALSceneShaker::update(bool &MUSTWAIT) {
    MUSTWAIT = true;
    curX = maxX == 0? 0 : qrand()%(maxX*2) - maxX;
    curY = maxY == 0? 0 : qrand()%(maxY*2) - maxY;
    duration --;
    if (duration <= 0) {
        curX = 0;
        curY = 0;
        MUSTWAIT = false;
    }
}
