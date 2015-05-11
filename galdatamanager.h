#ifndef GALDATAMANAGER_H
#define GALDATAMANAGER_H

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QImage>
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
    map<QString, QImage> charImg[10];
    QImage scene[10];
    void refresh();
    void mouseMove(QMouseEvent *e);
    void paint(QPainter &painter);
    QString status;
    GALScenePainter galScenePainter;
    int focus;
};

#endif // GALDATAMANAGER_H
