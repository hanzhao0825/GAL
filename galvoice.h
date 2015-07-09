#ifndef GALVOICE_H
#define GALVOICE_H


#include <QMediaPlayer>
#include <QMediaPlayList>
#include <QFile>
#include <QDir>
class GALVoice
{
public:
    GALVoice();
    ~GALVoice();
    void play(QString voice);

    QMediaPlayer voice;
    QMediaPlaylist playlist;
};

#endif // GALVOICE_H
