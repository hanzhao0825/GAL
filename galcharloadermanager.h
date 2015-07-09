#ifndef GALCHARLOADERMANAGER_H
#define GALCHARLOADERMANAGER_H

#include <QThread>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QDirIterator>
#include "galcharloader.h"
class GALCharLoaderManager
{
public:
    GALCharLoaderManager();
    ~GALCharLoaderManager();
    GALCharLoader galCharLoader[100];
    int nextID;
    void load(QString name, map<pair<QString, QString>, QPixmap> *img, map<pair<QString, QString>, pair<int, int> > *pos);
};

#endif // GALCHARLOADERMANAGER_H
