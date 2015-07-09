#include "galcharloader.h"

GALCharLoader::GALCharLoader()
{


}

GALCharLoader::~GALCharLoader()
{

}

void GALCharLoader::run() {
    if ((*pos)[make_pair("","")] == make_pair(1,1)) return;
    (*pos)[make_pair("","")] = make_pair(1,1);
    //QString path = QDir::toNativeSeparators(QApplication::applicationDirPath+"/res/gal/image/char/"+name+"/");
    QString path = QDir::toNativeSeparators(":/res/gal/image/char/"+name+"/");
    QDir dir(path);
    if(!dir.exists())
    {
        return;
    }

    QStringList filters;
    filters << QString("*.png");

    QDirIterator dir_iterator(path,
        filters,
        QDir::Files | QDir::NoSymLinks,
        QDirIterator::Subdirectories);
    while(dir_iterator.hasNext())
    {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString fname = file_info.fileName();
        QStringList sl = fname.left(fname.length()-4).split("_");
        (*img)[make_pair(sl[0], sl[1])] = QPixmap(file_info.absoluteFilePath());
    }

    QFile f(QDir::toNativeSeparators(":/res/gal/image/char/"+name+"/data.txt"));
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "GALStatus::loadFrom - Cannot open file";
        return;
    }
    QTextStream fin(&f);
    int sum = fin.readLine().toInt();
    for (int i = 0; i < sum; i ++) {
        QString str = fin.readLine();
        QStringList sl1 = str.split(" ");
        QStringList sl2 = sl1[0].left(sl1[0].length()-4).split("_");
        (*pos)[make_pair(sl2[0], sl2[1])] = make_pair(sl1[1].toInt(), sl1[2].toInt());
    }
    f.close();
    (*pos)[make_pair("","")] = make_pair(0,0);
}

void GALCharLoader::init(QString name, map<pair<QString, QString>, QPixmap> *img, map<pair<QString, QString>, pair<int, int> > *pos) {
    this->name = name;
    this->img = img;
    this->pos = pos;
}
