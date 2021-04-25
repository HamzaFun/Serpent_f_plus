#include "music.h"

#include <QMediaPlaylist>
#include <QMediaPlayer>

Music::Music(QString media, QObject* parent):QMediaPlayer(parent)
{
    QMediaPlaylist* playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/Sounds/"+media));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    setVolume(50);
    setPlaylist(playlist);
}

void Music::playMusic()
{
    if (state() == QMediaPlayer::StoppedState)
    {
        play();
    }
}

void Music::stopMusic()
{
    if (state() == QMediaPlayer::PlayingState) {
        stop();
    }
}
