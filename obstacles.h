#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QGraphicsRectItem>

class Obstacles : public QGraphicsRectItem
{
public:
    Obstacles(int Num,QGraphicsItem* parent=0);
    void ajouterMurPart(int x,int y);
    QString type;
    int ObsCourant;
    int maxScore;
    QString bg;
private:
    void crearObs1();
    void crearObs2();

};

#endif // OBSTACLES_H
