#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>

class Music : public QMediaPlayer
{
public:
    Music(QString media,QObject* parent = 0);

    void playMusic();
    void stopMusic();

};

#endif // MUSIC_H
