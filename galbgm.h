#ifndef GALBGM_H
#define GALBGM_H

#include <QString>

#include <QMediaPlayer>
#include <QMediaPlayList>
#include <QApplication>
#include <QFile>
#include <QDir>
class GALBGM
{
public:
    GALBGM();
    ~GALBGM();
    void play(QString bgm, QString curPath);
    void stop();

    QMediaPlayer bgm;
    QMediaPlaylist playlist;
};

#endif // GALBGM_H
