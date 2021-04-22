#ifndef JEU_H
#define JEU_H

#include <QGraphicsView>
#include "animerserpent.h"
#include "button.h"
#include "obstacles.h"
#include "score.h"

class Jeu : public QGraphicsView
{
    Q_OBJECT
public:
    Jeu(QWidget* parent=0);
    void keyPressEvent(QKeyEvent *event);
    Score* score;
    QGraphicsScene* sceneDeJeu;
    AnimerSerpent* serp;
    AnimerSerpent* serp2;
    int stg;

    void afficherMenu(QString titre, QString jouer);
    QGraphicsTextItem* titreText = NULL;
    QGraphicsTextItem* pauseText = NULL;
    QGraphicsTextItem* choixText = NULL;
    QGraphicsTextItem* stagesText = NULL;
    Obstacles* obs = NULL;
    Button* b;
    void finJeu();
private:
    Button* creerStg(QString text, int w, int h, int xpos, int ypos, int stg, bool debut, QGraphicsTextItem* pere);
public slots:
    void debut();
    void creerObs(int);
    void afficherStages();
    void afficherPause();
    void choix();
    void retourAffich();
    void commancer();
    void routeurMenu();

};

#endif // JEU_H
