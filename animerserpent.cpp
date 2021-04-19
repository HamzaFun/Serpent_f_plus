#include "animerserpent.h"
#include "fruit.h"
#include <QDebug>
#include <QTimer>
#include <qevent.h>

AnimerSerpent::AnimerSerpent(QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    serpTete = new SerpPart(this);
    serpTete->setSuiv(NULL);
    serpTete->setPreced(NULL);
    serpTete->setPos(200,200);
    serpTete->setDirection("RIGHT");
    serpTete->part = "HEAD";
    serpTete->setImage();
    serpQueue = serpTete;

    t = new QTimer();
    connect(t, SIGNAL(timeout()), this, SLOT(move()));

    fruitT = new QTimer();
    connect(fruitT, SIGNAL(timeout()), this, SLOT(ajouterFruit()));

    fruit2T = new QTimer();
    connect(fruit2T, SIGNAL(timeout()), this, SLOT(ajouterFruit2()));

    direction = "RIGHT";

    ajoutePart();
    ajoutePart();
    ajoutePart();

//    text = new QGraphicsTextItem(this);


}

void AnimerSerpent::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Down && serpTete->Direction() != "UP") {
      //  snake->setY(snake->y()+40);
        direction = "DOWN";
    }
    else if(event->key() == Qt::Key_Up &&serpTete->Direction()  != "DOWN") {
      //  snake->setY(snake->y()-40);
        direction = "UP";
    }
    else if(event->key() == Qt::Key_Right && serpTete->Direction()  != "LEFT") {
      //  snake->setX(snake->x()+40);
        direction = "RIGHT";
    }
    else if(event->key() == Qt::Key_Left && serpTete->Direction()  != "RIGHT") {
        //snake->setX(snake->x()-40);
        direction = "LEFT";
    }
    else if(event->key() == Qt::Key_Space){
        if(t->isActive() ){
            t->stop();

            fruitT->stop();
            fruit2T->stop();
        }
        else{
            fruitT->start(3000);
            fruit2T->start(7000);
            t->start(90);
        }

    }
}

void AnimerSerpent::ajoutePart()
{
    SerpPart* part = new SerpPart(this);
    SerpPart* temp = serpTete;

    while(temp->Preced() != NULL){
        temp = temp->Preced();
    }
    temp->setPreced(part);
    part->setSuiv(temp);
    part->setPreced(NULL);
    part->ajouterDerrier();
    part->setDirection(temp->Direction());
    serpQueue = part;
    part->part = "TAIL";
    if(temp != serpTete)
        temp->part = "PART";
    part->setImage();
    temp->setImage();
}

void AnimerSerpent::animer()
{
    SerpPart* temp = serpQueue;

    while(temp != NULL){
        temp->move();
        temp = temp->Suiv();
    }
}

void AnimerSerpent::move()
{
    serpTete->setDirection(direction);
    animer();
}

void AnimerSerpent::ajouterFruit()
{
    Fruit* f1 = new Fruit("POMME", this);
    f1->setX(qrand() % (1200/40)*40);
    f1->setY(qrand() % (600/40)*40);
//    (*nbrFruit)++;
}

void AnimerSerpent::ajouterFruit2()
{
    Fruit* f1 = new Fruit("", this);
    f1->setX(qrand() % (1200/40)*40);
    f1->setY(qrand() % (600/40)*40);
//    (*nbrFruit)++;
}




