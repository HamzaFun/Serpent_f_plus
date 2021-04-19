#include "button.h"
#include "jeu.h"

#include <QGraphicsPixmapItem>

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
    bg->setPixmap(QPixmap(":/images/bg.jpg").scaled(1200,600));
    sceneDeJeu->addItem(bg);
    setScene(sceneDeJeu);

}

void Jeu::keyPressEvent(QKeyEvent *event)
{
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
    int yPos = 150;
    titreText->setPos(xPos, yPos);
    sceneDeJeu->addItem(titreText);

    Button* joue = new Button(jouer, titreText);
    int pxPos = 100 ;
    int pyPos = 160;
    joue->setPos(pxPos,pyPos);

    connect(joue,SIGNAL(clicked()) , this , SLOT(debut()));

    Button * quit = new Button("Quit",titreText);
    int qxPos = 100;
    int qyPos = 230;
    quit->setPos(qxPos,qyPos);
    connect(quit, SIGNAL(clicked()),this,SLOT(close()));

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
    sceneDeJeu->removeItem(titreText);
    delete titreText;

}
