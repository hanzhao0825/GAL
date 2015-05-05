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

    QMediaPlayer bgm;
    QMediaPlaylist playlist;
};

#endif // GALBGM_H
