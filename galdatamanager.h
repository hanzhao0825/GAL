#ifndef GALDATAMANAGER_H
#define GALDATAMANAGER_H

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QTime>
#include <map>
#include "galstatus.h"
#include "galscenepainter.h"

class GALDataManager
{
public:
    GALDataManager();
    ~GALDataManager();
    GALStatus galStatus[10];
    void refresh();
    void mouseMove(QMouseEvent *e);
    void paint(QPainter &painter);
    QString status;
    int focus;
};

#endif // GALDATAMANAGER_H
