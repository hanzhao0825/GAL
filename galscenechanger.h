#ifndef GALSCENECHANGER_H
#define GALSCENECHANGER_H

#include <QString>

class GALSceneChanger
{
public:
    GALSceneChanger();
    ~GALSceneChanger();
    void update();

    QString status;
    int duration;
};

#endif // GALSCENECHANGER_H
