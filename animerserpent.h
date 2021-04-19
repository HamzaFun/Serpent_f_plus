#ifndef ANIMERSERPENT_H
#define ANIMERSERPENT_H

#include "serppart.h"
#include <QGraphicsRectItem>
#include <QObject>

class AnimerSerpent :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    AnimerSerpent(QGraphicsItem* prent=0);
    void keyPressEvent(QKeyEvent *event);
    void ajoutePart();
    void animer();


public slots:
    void move();
    void ajouterFruit();
    void ajouterFruit2();

private:
    SerpPart* serpTete;
    SerpPart* serpQueue;
    QString direction;
    QTimer* t;
    QTimer* fruitT;
    QTimer* fruit2T;
    QGraphicsTextItem* text;

};

#endif // ANIMERSERPENT_H
