#include "murpart.h"
#include "obstacles.h"

Obstacles::Obstacles(int Num,QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    switch(Num){
    case 1:
        crearObs1();
        break;
    case 2:
        crearObs2();
        break;
    default:
        break;
    }

}

void Obstacles::ajouterMurPart(int x, int y)
{
    MurPart* part = new MurPart(this);
    part->setPos(x,y);
}

void Obstacles::crearObs1()
{
    MurPart* mur = new MurPart(this);
    mur->setPos(0,0);
    int s=40;
    for(int i =0; i < 29; ++i){
        ajouterMurPart(s,0);
        s+=40;
    }
    s=40;
    for(int i =0; i < 29; ++i){
        ajouterMurPart(s,560);
        s+=40;
    }
    s=40;
    for(int i =0; i < 14; ++i){
        ajouterMurPart(0,s);
        s+=40;
    }
    s=40;
    for(int i =0; i < 14; ++i){
        ajouterMurPart(1160,s);
        s+=40;
    }

}

void Obstacles::crearObs2()
{
    MurPart* mur = new MurPart(this);
    mur->setPos(1200-mur->boundingRect().width(),0);

    MurPart* mur1 = new MurPart(this);
    mur1->setPos(1200-2*mur->boundingRect().width(),0);
}
