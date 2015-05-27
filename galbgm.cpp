#include "galbgm.h"

GALBGM::GALBGM()
{

}

GALBGM::~GALBGM()
{

}

void GALBGM::play(QString bgmName) {
    playlist.clear();
    playlist.addMedia(QUrl::fromLocalFile(bgmName));
    playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgm.setPlaylist(&playlist);
    bgm.setVolume(20);
    bgm.play();
}

void GALBGM::stop() {
    bgm.stop();
}
