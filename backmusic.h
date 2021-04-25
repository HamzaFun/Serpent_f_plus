#ifndef BACKMUSIC_H
#define BACKMUSIC_H

#include <QMediaPlayer>
#include "music.h"

class BackMusic : public QObject
{
public:
    BackMusic(QObject* parent=0);

    Music* background_music;
    Music* menu_music;
    Music* findejeu_music;
};

#endif // BACKMUSIC_H
