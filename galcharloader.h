#ifndef GALCHARLOADER_H
#define GALCHARLOADER_H

#include <QThread>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QDirIterator>
#include <QFile>

using namespace std;
class GALCharLoader : public QThread
{
public:
    GALCharLoader();
    ~GALCharLoader();
    void init(QString name, map<pair<QString, QString>, QPixmap> *img, map<pair<QString, QString>, pair<int, int> > *pos);
    void run();
    QString name;
    map<pair<QString, QString>, QPixmap> *img;
    map<pair<QString, QString>, pair<int, int> >  *pos;
};

#endif // GALCHARLOADER_H
