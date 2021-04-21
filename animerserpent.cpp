#include "animerserpent.h"
#include "fruit.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include <qevent.h>
#include "jeu.h"

extern Jeu* jeu;

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
    ajouterFruit();
    for(int i=0;i<10; ++i ){
        ajouterFruit2();
    }
    fruitT = new QTimer();
    connect( serpTete, SIGNAL(manger()), this, SLOT(ajouterFruit()));

    fruit2T = new QTimer();
//    connect(fruit2T, SIGNAL(timeout()), this, SLOT(ajouterFruit2()));

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
    else if( event->key() == Qt::Key_Escape){
        if(t->isActive()){
            t->stop();
            fruitT->stop();
            fruit2T->stop();
            jeu->afficherMenu("Jeu Serpent ", "Recommencer");
        }
        else{
            fruitT->start(3000);
            fruit2T->start(7000);
            t->start(90);
            if(jeu->titreText != NULL)
            {
                qDebug() << "eshape start";
                jeu->sceneDeJeu->removeItem(jeu->titreText);
                delete jeu->titreText;
                jeu->titreText = NULL;
                qDebug() << "eshape suppression";
            }
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
    int x ;
    int y ;
    int k=1;
    while(k != 0){
        k=0;

    QList <QGraphicsItem* > coll = jeu->sceneDeJeu->items();
    x = QRandomGenerator::global()->generate() % (1160/40)*40 ;
    y = QRandomGenerator::global()->generate() % (560/40)*40 ;

    for(int i=0; i < coll.length(); ++i){
        if(coll[i]->pos().x() == x && coll[i]->pos().y() == y ) {
            k++;
            break;
        }
    }
    }
    f1->setX(x);
    f1->setY(y);

}

void AnimerSerpent::ajouterFruit2()
{
    Fruit* f1 = new Fruit("", this);
    int x ;
    int y ;
    int k=1;
    while(k != 0){
        k=0;

    QList <QGraphicsItem* > coll = jeu->sceneDeJeu->items();
    x = QRandomGenerator::global()->generate() % (1160/40)*40 ;
    y = QRandomGenerator::global()->generate() % (560/40)*40 ;

    for(int i=0; i < coll.length(); ++i){
        if(coll[i]->pos().x() == x && coll[i]->pos().y() == y ) {
            k++;
            break;
        }
    }
    }
    f1->setX(x);
    f1->setY(y);

}




