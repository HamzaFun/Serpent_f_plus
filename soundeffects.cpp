#include "soundeffects.h"

SoundEffects::SoundEffects(QObject *parent) : QObject(parent)
, dir("qrc:/Sounds/sfx/")
{
    coin_1 = new QMediaPlayer();
    coin_1->setMedia(QUrl(dir+"coin.wav"));
    connect(this, SIGNAL(coin1()), this, SLOT(coin1s()));
    coin_2 = new QMediaPlayer();
    coin_2->setMedia(QUrl(dir+"coin1.wav"));
    connect(this, SIGNAL(coin2()), this, SLOT(coin2s()));
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
void SoundEffects::coin2s()
{
    if (coin_2->state() == QMediaPlayer::PlayingState) {
        coin_2->setPosition(0);
    }else if (coin_2->state() == QMediaPlayer::StoppedState)
    {
        coin_2->play();
    }
}
