#ifndef JEU_H
#define JEU_H

#include <QGraphicsView>
#include "animerserpent.h"
#include "button.h"

class Jeu : public QGraphicsView
{
    Q_OBJECT
public:
    Jeu(QWidget* parent=0);
    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene* sceneDeJeu;
    AnimerSerpent* serp;


    void afficherMenu(QString titre, QString jouer);
    QGraphicsTextItem* titreText;
    Button* b;
    void finJeu();
public slots:
    void debut();


};

#endif // JEU_H
