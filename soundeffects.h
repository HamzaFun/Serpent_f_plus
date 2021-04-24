#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class SoundEffects : public QObject
{
    Q_OBJECT
public:
    explicit SoundEffects(QObject *parent = nullptr);

    QString dir;
    QMediaPlayer* coin_1;
private slots:
    void coin1s();
    void coin2s();
signals:
    void coin1(); void coin2();
};

#endif // SOUNDEFFECTS_H
