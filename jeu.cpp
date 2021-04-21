#include "button.h"
#include "jeu.h"
#include "murpart.h"
#include "obstacles.h"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPushButton>
#include <QStyle>

Jeu::Jeu(QWidget *parent):QGraphicsView(parent)
{
    // charger la vue :
    setFixedSize(1200,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // charger la scene de jeu
    sceneDeJeu = new QGraphicsScene(this);
    sceneDeJeu->setSceneRect(0,0,1200,600);
    QGraphicsPixmapItem* bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/bg1.jpg").scaled(1200,600));
    bg->setZValue(0);
    sceneDeJeu->addItem(bg);
    setScene(sceneDeJeu);

    serp2 =NULL;
    serp = NULL;
}

void Jeu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape :

        break;
    default:
        break;
    }
    if(serp){
        serp->keyPressEvent(event);
    }else
        QGraphicsView::keyPressEvent(event);

}

void Jeu::afficherMenu(QString titre, QString jouer)
{
    titreText = new QGraphicsTextItem(titre);
    QFont titreFont("arial", 50 );
    titreText->setFont(titreFont);
    int xPos = width()/2 - titreText->boundingRect().width()/2;
    int yPos = 100;
    titreText->setPos(xPos, yPos);
    sceneDeJeu->addItem(titreText);

    Button* menu = new Button("STAGES", 150,40, titreText);
    int mxPos = 100 ;
    int myPos = 120;
    menu->setPos(mxPos,myPos);

    connect(menu, SIGNAL(clicked()), this, SLOT(afficherStages()));

    Button* joue = new Button(jouer,150,40, titreText);
    int pxPos = 100 ;
    int pyPos = 170;
    joue->setPos(pxPos,pyPos);

    connect(joue,SIGNAL(clicked()) , this , SLOT(debut()));

    Button * quit = new Button("Quit",150,40,titreText);
    int qxPos = 100;
    int qyPos = 220;
    quit->setPos(qxPos,qyPos);
    connect(quit, SIGNAL(clicked(int)),this,SLOT(close()));

}

void Jeu::finJeu()
{
    afficherMenu("Game Over", "ReJeouer !!");
    sceneDeJeu->removeItem(serp);

}

void Jeu::debut()
{
    serp = new AnimerSerpent();
    serp->setFlag(QGraphicsItem::ItemIsFocusable);
    serp->setFocus();
    sceneDeJeu->addItem(serp);
//    if(stg == 1){
//        qDebug() << "choisir stage 1";
//        Obstacles* obs = new Obstacles(1);
//        sceneDeJeu->addItem(obs);
//    }
//    emit customObs(1);
    if(titreText != NULL){
        qDebug() << "suppression  :" << titreText->textWidth();
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText = NULL;
    }
    if(stagesText != NULL){
        sceneDeJeu->removeItem(stagesText);
        delete stagesText;
        qDebug() << "suppresion menu text";
        stagesText = NULL;
    }
    if(serp2) serp2->deleteLater();
    serp2 = serp;
}


void Jeu::creerObs(int NumObs)
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
        qDebug() << "suppression Obs";
    }
    if(NumObs != 0 && obs == NULL){
    obs = new Obstacles(NumObs);
    sceneDeJeu->addItem(obs);
    }
    debut();
}

void Jeu::afficherStages()
{
    sceneDeJeu->removeItem(titreText);
    delete titreText;
    titreText =NULL;

    stagesText = new QGraphicsTextItem("Stages");
    QFont titreFont("arial", 50 );
    stagesText->setFont(titreFont);
    int xPos = width()/2 - stagesText->boundingRect().width()/2;
    int yPos = 100;
    stagesText->setPos(xPos, yPos);
    sceneDeJeu->addItem(stagesText);

    Button* stage = new Button("1", 50, 50, stagesText);
    int sx = 50;
    int sy = 100;
    stage->setPos(sx,sy);
    stage->stgNum = 1;
    connect(stage, SIGNAL(clicked(int)), this, SLOT(creerObs(int)));

    Button* stage2 = new Button("2", 50, 50, stagesText);
    int s2x = 100;
    int s2y = 100;
    stage2->setPos(s2x,s2y);
    stage2->stgNum = 2;
    connect(stage2, SIGNAL(clicked(int)), this, SLOT(creerObs(int)));

    Button* retour = new Button("<< RETOUR", 100, 50, stagesText);
    int rx = 20;
    int ry = 400;
    retour->setPos(rx,ry);
    connect(retour, SIGNAL(clicked()), this, SLOT(retourAffich()));

}

void Jeu::retourAffich()
{
    if(stagesText){
//        qDebug() << "retour sign";
        sceneDeJeu->removeItem(stagesText);
        delete stagesText;
    }
    afficherMenu("Jeu Serpent ", "Jouer");

}


