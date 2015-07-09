#include "galvoice.h"

GALVoice::GALVoice()
{

}

GALVoice::~GALVoice()
{

}

void GALVoice::play(QString voiceName) {
    playlist.clear();
    if (!QFile::exists(QDir::toNativeSeparators(voiceName))) return;
    playlist.addMedia(QUrl::fromLocalFile(voiceName));
    try{
        voice.stop();
        voice.setPlaylist(&playlist);
        voice.setVolume(100);
        voice.play();
    } catch (QString e) {

    }
}
