#ifndef JEU_H
#define JEU_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include "animerserpent.h"
#include "button.h"
#include "obstacles.h"
#include "score.h"
#include "soundeffects.h"
#include "music.h"

class Jeu : public QGraphicsView
{
    Q_OBJECT
public:
    Jeu(QWidget* parent=0);
    QGraphicsScene* sceneDeJeu;
    SoundEffects* sfx;
    AnimerSerpent* serp;
    AnimerSerpent* serp2;

    Music kjh;

    QGraphicsTextItem* titreText = NULL;
    QGraphicsTextItem* pauseText = NULL;
    QGraphicsTextItem* choixText = NULL;
    QGraphicsTextItem* stagesText = NULL;

    Score* score;
    Obstacles* obs = NULL;
    Button* b;

    Music* background_music;
    Music* menu_music;
    Music* findejeu_music;

    int stg;
    int StageCourant;

    void keyPressEvent(QKeyEvent *event);
    void afficherMenu(QString titre, QString jouer);
    void afficherFin(QString titre, QString jouer);
    void finJeu();
private:
    QGraphicsPixmapItem* background;
    QMediaPlayer* creerMusic(QString music);
    Button* creerStg(QString text, int w, int h, int xpos, int ypos, int stg, bool debut, QGraphicsTextItem* pere);
    QString font;
public slots:
    void debut();
    void creerObs(int);
    void afficherStages();
    void afficherPause();
    void choix();
    void retourAffich();
    void commancer();
    void routeurMenu();
    void stageSuiv();

};

#endif // JEU_H
