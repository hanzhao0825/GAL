#include "galcharloadermanager.h"

GALCharLoaderManager::GALCharLoaderManager()
{
    nextID = 0;
}

GALCharLoaderManager::~GALCharLoaderManager()
{

}

void GALCharLoaderManager::load(QString name, map<pair<QString, QString>, QPixmap> *img, map<pair<QString, QString>, pair<int, int> > *pos) {
    galCharLoader[nextID].init(name, img, pos);
    galCharLoader[nextID].start();
    nextID ++;
    if (nextID == 100) nextID = 0;
}
