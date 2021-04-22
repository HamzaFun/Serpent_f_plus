#include "button.h"
#include "jeu.h"
#include "murpart.h"
#include "obstacles.h"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPushButton>
#include <QStyle>
#include <QTimer>

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

    score =new Score();
    sceneDeJeu->addItem(score);
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

    Button* joue = creerStg(jouer, 150, 40, 100, 170, 0, true, titreText);
    Button* quit = creerStg("QUIT", 150, 40, 100,220, 0, false, titreText);

    Q_UNUSED(joue);
    Q_UNUSED(quit);

}

void Jeu::finJeu()
{
    afficherMenu("Game Over", "ReJeouer !!");
    sceneDeJeu->removeItem(serp);

}

Button* Jeu::creerStg(QString text, int w, int h, int xpos, int ypos, int stg, bool debut, QGraphicsTextItem *pere)
{
    Button* button = new Button(text, w, h, pere);
    button->setPos( xpos, ypos);
    if(stg != 0) {
        button->stgNum = stg;
        connect(button, SIGNAL(clicked(int)),this,SLOT(creerObs(int)));
    }
    else if(debut) connect(button, SIGNAL(clicked(int)),this,SLOT(debut()));
    else  connect(button, SIGNAL(clicked(int)),this,SLOT(close()));

    return button;
}



void Jeu::debut()
{
    serp = new AnimerSerpent();
    serp->setFlag(QGraphicsItem::ItemIsFocusable);
    serp->setFocus();
    sceneDeJeu->addItem(serp);
    score->setVisible(true);
    score->setScore(0);
    if(pauseText != NULL){
        sceneDeJeu->removeItem(pauseText);
        delete pauseText;
        pauseText = NULL;
    }
    if(titreText != NULL){
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText = NULL;
    }
    if(stagesText != NULL){
        sceneDeJeu->removeItem(stagesText);
        delete stagesText;
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
    }
    if(NumObs != 0 && obs == NULL){
    obs = new Obstacles(NumObs);
    sceneDeJeu->addItem(obs);
    }
    debut();
}

void Jeu::afficherStages()
{
    if(titreText != NULL){
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText =NULL;
    }

    stagesText = new QGraphicsTextItem("Stages");
    QFont titreFont("arial", 50 );
    stagesText->setFont(titreFont);
    int xPos = width()/2 - stagesText->boundingRect().width()/2;
    int yPos = 100;
    stagesText->setPos(xPos, yPos);
    sceneDeJeu->addItem(stagesText);

    Button* stage = creerStg("1", 50, 50, 0,100, 1, true, stagesText);
    Button* stage2 = creerStg("2", 50, 50, 50,100, 2, true, stagesText);
//    stage2->setAcceptedMouseButtons(Qt::NoButton);
//    if(stage2->acceptedMouseButtons() == Qt::NoButton) stage2->setAcceptHoverEvents(false);
    Button* stage3 = creerStg("3", 50, 50, 100,100, 3, true, stagesText);
    Button* stage4 = creerStg("4", 50, 50, 150,100, 4, true, stagesText);

    Button* retour = new Button("<< RETOUR", 100, 50, stagesText);
    int rx = 20;
    int ry = 400;
    retour->setPos(rx,ry);
    connect(retour, SIGNAL(clicked()), this, SLOT(retourAffich()));

    Q_UNUSED(stage);
    Q_UNUSED(stage2);
    Q_UNUSED(stage3);
    Q_UNUSED(stage4);
}

void Jeu::afficherPause()
{
    if(choixText != NULL)
    {
        sceneDeJeu->removeItem(choixText);
        delete choixText;
        choixText = NULL;
    }
    pauseText = new QGraphicsTextItem("PAUSE");
    QFont titreFont("arial", 50 );
    pauseText->setFont(titreFont);
    int xPos = width()/2 - pauseText->boundingRect().width()/2;
    int yPos = 100;
    pauseText->setPos(xPos, yPos);
    sceneDeJeu->addItem(pauseText);
    Button* commancer = new Button("COMMANCER", 150, 40, pauseText);
    commancer->setPos(100,140);
    connect(commancer, SIGNAL(clicked()), this, SLOT(commancer()) );
    Button* recommancer = creerStg("Recommancer", 150, 40, 100, 170, 0, true, pauseText);
    Button* routeur = new Button("<< RETOUR", 100, 50, pauseText);
    int rx = 20;
    int ry = 400;
    routeur->setPos(rx,ry);
    connect(routeur, SIGNAL(clicked()), this, SLOT(choix()) );

    Q_UNUSED(recommancer);
    Q_UNUSED(routeur);
}

void Jeu::choix()
{
    if(pauseText != NULL)
    {
        sceneDeJeu->removeItem(pauseText);
        delete pauseText;
        pauseText = NULL;
    }
    choixText = new QGraphicsTextItem("WARNING");
    QFont titreFont("arial", 50 );
    choixText->setFont(titreFont);
    int xPos = width()/2 - choixText->boundingRect().width()/2;
    int yPos = 100;
    choixText->setPos(xPos, yPos);
    sceneDeJeu->addItem(choixText);
    Button* oui = new Button("OUI", 50, 50, choixText);
    int rx = 30;
    int ry = 100;
    oui->setPos(rx,ry);
    connect(oui, SIGNAL(clicked()), this, SLOT(routeurMenu()) );
    Button* non = new Button("NON", 50, 50, choixText);
    int nx = 100;
    int ny = 100;
    non->setPos(nx,ny);
    connect(non, SIGNAL(clicked()), this, SLOT(afficherPause()) );
}

void Jeu::retourAffich()
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    if(stagesText != NULL){
        sceneDeJeu->removeItem(stagesText);
        delete stagesText;
        stagesText = NULL;
    }
    afficherMenu("Jeu Serpent ", "Jouer");

}

void Jeu::commancer()
{
    if(!serp->t->isActive()){
        serp->t->start(90);
        if(titreText != NULL)
        {
            sceneDeJeu->removeItem(titreText);
            delete titreText;
            titreText = NULL;
        }
        if(pauseText != NULL)
        {
            sceneDeJeu->removeItem(pauseText);
            delete pauseText;
            pauseText = NULL;
        }
    }

}

void Jeu::routeurMenu()
{
    sceneDeJeu->removeItem(serp);
//    delete serp;
    if(choixText != NULL)
    {
        sceneDeJeu->removeItem(choixText);
        delete choixText;
        choixText = NULL;
    }
    if(pauseText != NULL){
        sceneDeJeu->removeItem(pauseText);
        delete pauseText;
        pauseText = NULL;
    }
    afficherMenu("Jeu Serpent ", "Jouer");
}


