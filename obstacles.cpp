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
    case 3:
        crearObs3();
        maxScore = 4;
        break;
    case 4:
        crearObs4();
        maxScore = 4;
        break;
    case 5:
        crearObs5();
        maxScore = 4;
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
}

void Obstacles::crearObs3()
{
    bg = ":/bg/bg/bg2.png";
    int s=0;
    for(int i=0; i < 15; ++i){
        ajouterMurPart(560,s);
        s +=40;
    }
    s=0;
    for(int i=0; i < 14; ++i){
        ajouterMurPart(s,280);
        s +=40;
    }
    s=600;
    for(int i=0; i < 15; ++i){
        ajouterMurPart(s,280);
        s +=40;
    }
}

void Obstacles::crearObs4()
{
    bg = ":/bg/bg/bg1.jpg";
    MurPart* mur = new MurPart(this);
    mur->setPos(0,0);
    int s=0;
    for(int i =0; i < 15; ++i){
        ajouterMurPart(560,s);
        s+=40;
    }
    s=600;
    for(int i =0; i < 15; ++i){
        ajouterMurPart(s,0);
        ajouterMurPart(s,560);
        s+=40;
    }
    s=40;
    for(int i =0; i < 7; ++i){
        ajouterMurPart(0,s);
        ajouterMurPart(1160,s);
        s+=40;
    }
    s=120;
    for(int i =0; i < 11; ++i){
        ajouterMurPart(s,280);
        s+=40;
    }
    s=600;
    for(int i =0; i < 12; ++i){
        ajouterMurPart(s,280);
        s+=40;
    }
}

void Obstacles::crearObs5()
{
    bg = ":/bg/bg/bg3.jpg";
    MurPart* mur = new MurPart(this);
    mur->setPos(0,0);
    int s=40;
    for(int i =0; i < 13; i++){
        ajouterMurPart(s,0);
        s+=40;
    }
    s=0;
    for(int i =0; i < 14; i++){
        ajouterMurPart(s,560);
        s+=40;
    }
    s=0;
    for(int i =0; i < 30; i++){
        ajouterMurPart(s,240);
        s+=40;
    }
    s=0;
    for(int i =0; i < 5; i++){
        ajouterMurPart(s,360);
        s+=40;
    }
    s=320;
    for(int i =0; i < 22; i++){
        ajouterMurPart(s,360);
        s+=40;
    }
    s=0;
    for(int i =0; i < 4; i++){
        ajouterMurPart(560,s);
        s+=40;
    }
    s=280;
    for(int i =0; i < 2; i++){
        ajouterMurPart(560,s);
        s+=40;
    }
    s=400;
    for(int i =0; i < 5; i++){
        ajouterMurPart(560,s);
        s+=40;
    }
}
