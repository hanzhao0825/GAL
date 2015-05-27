#ifndef GALBGM_H
#define GALBGM_H

#include <QString>

#include <QMediaPlayer>
#include <QMediaPlayList>

class GALBGM
{
public:
    GALBGM();
    ~GALBGM();
    void play(QString bgm);
    void stop();

    QMediaPlayer bgm;
    QMediaPlaylist playlist;
};

#endif // GALBGM_H
