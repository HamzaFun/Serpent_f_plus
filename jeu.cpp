#include "button.h"
#include "jeu.h"
#include "murpart.h"
#include "obstacles.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QStyle>
#include <QTimer>
#include <QString>

Jeu::Jeu(QWidget *parent):QGraphicsView(parent)
, font("baloo 2")
{
    // charger la vue :
    setFixedSize(1200,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // charger la scene de jeu
    sceneDeJeu = new QGraphicsScene(this);
    background = new QGraphicsPixmapItem();
    sfx = new SoundEffects(this);

    sceneDeJeu->setSceneRect(0,0,1200,600);
    setScene(sceneDeJeu);

    background_music = new Music("ingame_music1.mp3", this);
    menu_music = new Music("menu_music2.mp3", this);
    findejeu_music = new Music("gameover_music.mp3");

    score =new Score();
    sceneDeJeu->addItem(score);
    serp2 =NULL;
    serp = NULL;
    setWindowIcon(QIcon(":/images/snake.ico"));

    StageCourant = 1;
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
void Jeu::afficherFin(QString titre, QString jouer)
{
    titreText = new QGraphicsTextItem(titre);
    titreText->setFont(QFont(font, 50));
    titreText->setPos(width()/2 - titreText->boundingRect().width()/2, 100);
    titreText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(titreText);

//    Button* stages = new Button("STAGES", 150,40, titreText);
//    int mxPos = titreText->boundingRect().width()/2 - stages->boundingRect().width()/2 ;
//    int myPos = 120;
//    stages->setPos(mxPos,myPos);
//    connect(stages, SIGNAL(clicked()), this, SLOT(afficherStages()));


    Button* joue = creerStg(jouer, 150, 40, titreText->boundingRect().width()/2 - 75, 170, 0, true, titreText);
    Button* quit = new Button("<< RETOUR", 150, 40, titreText);
    quit->setPos(titreText->boundingRect().width()/2 - quit->boundingRect().width()/2,220);
    connect(quit, SIGNAL(clicked()), this, SLOT(routeurMenu()));

    Q_UNUSED(joue);
    Q_UNUSED(quit);

}

void Jeu::afficherMenu(QString titre, QString jouer)
{
    findejeu_music->stopMusic();
    background_music->stopMusic();
    menu_music->playMusic();

    background->setPixmap(QPixmap(":/bg/menu.jpg").scaled(1200,600));
    background->setZValue(0);
    sceneDeJeu->addItem(background);
    titreText = new QGraphicsTextItem(titre);
    titreText->setDefaultTextColor(Qt::white);
    titreText->setFont(QFont(font, 50));
    titreText->setPos(width()/2 - titreText->boundingRect().width()/2, 150);
    sceneDeJeu->addItem(titreText);

    if(score->scoreText != NULL){
        sceneDeJeu->removeItem(score->scoreText);
        delete score->scoreText;
        score->scoreText = NULL;
    }

    Button* menu = new Button("STAGES", 150,40, titreText);
    menu->setPos(titreText->boundingRect().width()/2 - menu->boundingRect().width()/2,140);

    connect(menu, SIGNAL(clicked()), this, SLOT(afficherStages()));

    Button* joue = creerStg(jouer, 150, 40, titreText->boundingRect().width()/2 - 75, 190, 0, true, titreText);
    Button* quit = creerStg("QUITTER", 150, 40, titreText->boundingRect().width()/2 - 75, 240, 0, false, titreText);

    Q_UNUSED(joue);
    Q_UNUSED(quit);

}

void Jeu::finJeu()
{
    afficherFin("Fin De Jeu", "ReJeouer");
    score->afficherScore();
    background_music->stopMusic();
    findejeu_music->playMusic();
    sceneDeJeu->removeItem(serp);
    serp = NULL;
}

Button* Jeu::creerStg(QString text, int w, int h, int xpos, int ypos, int stg, bool debut, QGraphicsTextItem *pere)
{
    Button* button;
    if(stg != 0) {
        button = new Button(text, w, h, stg, true, pere);
        if(stg <= StageCourant){
            button->deletelock();
        }
        button->setHoverd();
        connect(button, SIGNAL(clicked(int)),this,SLOT(creerObs(int)));
    }
    else if(debut)
    {
        button = new Button(text, w, h, pere);
        connect(button, SIGNAL(clicked(int)),this,SLOT(debut()));
    }
    else {
        button = new Button(text, w, h, pere);
        connect(button, SIGNAL(clicked(int)),this,SLOT(close()));
    }

    button->setPos( xpos, ypos);
    return button;
}




void Jeu::debut()
{
    menu_music->stopMusic();
    findejeu_music->stopMusic();
    background_music->playMusic();
    if(obs == NULL){
    background->setPixmap(QPixmap(":/bg/bg4.png").scaled(1200,600));
    background->setZValue(0);
    sceneDeJeu->addItem(background);
    }
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
    if(score->scoreText != NULL){
        sceneDeJeu->removeItem(score->scoreText);
        delete score->scoreText;
        score->scoreText = NULL;
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
        background->setPixmap(QPixmap(obs->bg).scaled(1200,600));
        background->setZValue(0);
        sceneDeJeu->addItem(background);
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
    stagesText = new QGraphicsTextItem("STAGES");
    stagesText->setDefaultTextColor(Qt::white);
    stagesText->setFont(QFont(font, 50));
    stagesText->setPos(width()/2 - stagesText->boundingRect().width()/2, 100);
    stagesText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(stagesText);

    Button* stage = creerStg("1", 50, 50, -50,100, 1, true, stagesText);

    Button* stage2 = creerStg("2", 50, 50, 25 ,100, 2, true, stagesText);
    Button* stage3 = creerStg("3", 50, 50, 100,100, 3, true, stagesText);
    Button* stage4 = creerStg("4", 50, 50, 175,100, 4, true, stagesText);
    Button* stage5 = creerStg("5", 50, 50, 250,100, 5, true, stagesText);

    Button* retour = new Button("<< RETOUR", 100, 50, stagesText);
    retour->setPos(stagesText->boundingRect().width()/2 - retour->boundingRect().width()/2,400);
    connect(retour, SIGNAL(clicked()), this, SLOT(retourAffich()));


    Q_UNUSED(stage);
    Q_UNUSED(stage2);
    Q_UNUSED(stage3);
    Q_UNUSED(stage4);
    Q_UNUSED(stage5);
}

void Jeu::afficherPause()
{
    if(choixText != NULL)
    {
        sceneDeJeu->removeItem(choixText);
        delete choixText;
        choixText = NULL;
    }
    score->afficherScore();

    pauseText = new QGraphicsTextItem("PAUSE");
    pauseText->setFont(QFont("arial", 50 ));
    pauseText->setPos(width()/2 - pauseText->boundingRect().width()/2, 100);
    pauseText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(pauseText);
    Button* commancer = new Button("COMMANCER", 150, 40, pauseText);
    commancer->setPos(70,140);
    connect(commancer, SIGNAL(clicked()), this, SLOT(commancer()) );
    Button* recommancer = creerStg("Recommancer", 150, 40, 70, 200, 0, true, pauseText);
    Button* routeur = new Button("<< RETOUR", 100, 50, pauseText);
    routeur->setPos(80,400);
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
    if(titreText != NULL)
    {
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText = NULL;
    }
    if(score->scoreText != NULL){
        sceneDeJeu->removeItem(score->scoreText);
        delete score->scoreText;
        score->scoreText = NULL;
    }

    choixText = new QGraphicsTextItem("WARNING");
    choixText->setFont(QFont("arial", 50 ));
    choixText->setPos(width()/2 - choixText->boundingRect().width()/2, 100);
    choixText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(choixText);
    Button* oui = new Button("OUI", 50, 50, choixText);
    oui->setPos(110,100);
    connect(oui, SIGNAL(clicked()), this, SLOT(routeurMenu()) );
    Button* non = new Button("NON", 50, 50, choixText);
    non->setPos(180,100);
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
    if(titreText != NULL){
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText = NULL;
    }
    if(score->scoreText != NULL){
        sceneDeJeu->removeItem(score->scoreText);
        delete score->scoreText;
        score->scoreText = NULL;
    }

    background_music->stopMusic();
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
        if(score->scoreText != NULL){
            sceneDeJeu->removeItem(score->scoreText);
            delete score->scoreText;
            score->scoreText = NULL;
        }
    }

}

void Jeu::routeurMenu()
{
    sceneDeJeu->removeItem(serp);
    serp =NULL;
    if(choixText != NULL)
    {
        sceneDeJeu->removeItem(choixText);
        delete choixText;
        choixText = NULL;
    }
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
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
    if(score->scoreText != NULL){
        sceneDeJeu->removeItem(score->scoreText);
        delete score->scoreText;
        score->scoreText = NULL;
    }

    background_music->stopMusic();
    afficherMenu("Jeu Serpent ", "Jouer");
}

void Jeu::stageSuiv()
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    creerObs(StageCourant);
}


