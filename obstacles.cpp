#include "murpart.h"
#include "obstacles.h"

Obstacles::Obstacles(int Num,QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    ObsCourant = Num;
    switch(Num){
    case 1:
        crearObs1();
        maxScore = 2;
        break;
    case 2:
        crearObs2();
        maxScore = 3;
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
    bg = ":/bg/bg/bg1.jpg";
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
    bg = ":/bg/bg/bg2.png";
    MurPart* mur = new MurPart(this);
    mur->setPos(0,0);
    int s=40;
    for(int i =0; i < 29; ++i){
        ajouterMurPart(s,0);
        ajouterMurPart(s,560);
        s+=40;
    }
    s=40;
    for(int i =0; i < 4; ++i){
        ajouterMurPart(0,s);
        ajouterMurPart(1160,s);
        s+=40;
    }
    s=400;
    for(int i =0; i < 5; ++i){
        ajouterMurPart(0,s);
        ajouterMurPart(1160,s);
        s+=40;
    }
    s=320;
    for(int i =0; i < 14; ++i){
        ajouterMurPart(s,160);
        ajouterMurPart(s,400);
        s+=40;
    }
    MurPart* mur1 = new MurPart(this);
    mur1->setPos(mur->boundingRect().width(),0);
}


