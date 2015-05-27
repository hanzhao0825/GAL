#include "galscenechanger.h"

GALSceneChanger::GALSceneChanger()
{
    status = "X";
    duration = 0;
}

GALSceneChanger::~GALSceneChanger()
{

}

void GALSceneChanger::update() {
    if (duration == 0 || status == "X") return;
    duration -= 15;

}
