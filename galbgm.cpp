#include "galbgm.h"

GALBGM::GALBGM()
{

}

GALBGM::~GALBGM()
{

}

void GALBGM::play(QString bgmName, QString curPath) {

    if (!QFile::exists(QDir::toNativeSeparators(":/res/gal/bgm/"+bgmName))) return;

    QFile::remove(QDir::toNativeSeparators(curPath+"/res/gal/bgm/temp.mp3"));
    QFile::copy(QDir::toNativeSeparators(":/res/gal/bgm/"+bgmName) , QDir::toNativeSeparators(curPath+"/res/gal/bgm/temp.mp3"));
    playlist.clear();
    playlist.addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(curPath+"/res/gal/bgm/temp.mp3")));
    playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgm.setPlaylist(&playlist);
    bgm.setVolume(20);
    bgm.play();

}

void GALBGM::stop() {
    bgm.stop();
}
