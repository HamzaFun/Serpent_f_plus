#ifndef JEU_H
#define JEU_H

#include <QGraphicsView>
#include "animerserpent.h"
#include "button.h"
#include "obstacles.h"

class Jeu : public QGraphicsView
{
    Q_OBJECT
public:
    Jeu(QWidget* parent=0);
    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene* sceneDeJeu;
    AnimerSerpent* serp;
    AnimerSerpent* serp2;
    int stg;

    void afficherMenu(QString titre, QString jouer);
    QGraphicsTextItem* titreText = NULL;
    QGraphicsTextItem* stagesText = NULL;
    Obstacles* obs = NULL;
    Button* b;
    void finJeu();
public slots:
    void debut();
    void creerObs(int);
    void afficherStages();
    void retourAffich();
signals:
    void customObs(int);

};

#endif // JEU_H
