#ifndef GALSCENE_H
#define GALSCENE_H

#include <QPainter>
#include <QDebug>

class GALScene
{
public:
    GALScene();
    ~GALScene();
    void paint(QPainter &painter);
    int x;
};

#endif // GALSCENE_H
