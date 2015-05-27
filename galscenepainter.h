#ifndef GALSCENEPAINTER_H
#define GALSCENEPAINTER_H

#include <QPainter>
#include <QDebug>
#include <QImage>
#include <galstatus.h>
#include <map>
class GALScenePainter
{
public:
    GALScenePainter();
    ~GALScenePainter();
    void paint(QPainter &painter, int left, int top, double scale, GALStatus &galStatus);
};

#endif // GALSCENEPAINTER_H
