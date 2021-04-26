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

    QGraphicsTextItem* titreText = NULL;
    QGraphicsTextItem* pauseText = NULL;
    QGraphicsTextItem* choixText = NULL;
    QGraphicsTextItem* stagesText = NULL;
    QGraphicsTextItem* niveauText = NULL;
    Score* score;
    Obstacles* obs = NULL;
    Button* b;

    Music* background_music;
    Music* menu_music;
    Music* findejeu_music;

    Button::Niveau niv;

    int stg;
    int StageCourant;

    void keyPressEvent(QKeyEvent *event);
    void afficherMenu(QString titre, QString jouer);
    void afficherFin(QString titre, QString jouer);
    void afficherNiveau(QString titre, QString jouer);
    void finJeu();
private:
    QGraphicsPixmapItem* background;
    QMediaPlayer* creerMusic(QString music);
    Button* creerStg(QString text, int w, int h, int xpos, int ypos, int stg, QString debut, QGraphicsTextItem* pere);
    QString font;
    QGraphicsTextItem* textremove(QGraphicsTextItem* text);
    QGraphicsTextItem* creertext(QString titre, QString font,Qt::GlobalColor couleur);
public slots:
    void debut();
    void creerObs(int);
    void afficherStages();
    void afficherPause();
    void choix();
    void routeurMenu();
    void commancer();
    void stageSuiv();
    void niveau();
    void setNiv(Button::Niveau);
};

#endif // JEU_H
