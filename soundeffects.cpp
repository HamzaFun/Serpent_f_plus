#include "soundeffects.h"

SoundEffects::SoundEffects(QObject *parent) : QObject(parent)
, dir("qrc:/Sounds/sfx/")
{
    coin_1 = new QMediaPlayer();
    coin_1->setMedia(QUrl(dir+"coin.wav"));
    connect(this, SIGNAL(coin1()), this, SLOT(coin1s()));
}

void SoundEffects::coin1s()
{
    if (coin_1->state() == QMediaPlayer::PlayingState) {
        coin_1->setPosition(0);
    }else if (coin_1->state() == QMediaPlayer::StoppedState)
    {
        coin_1->play();
    }
}
