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
    background->setZValue(0);

    //initialiser la music
    background_music = new Music("ingame_music1.mp3", this);
    menu_music = new Music("menu_music2.mp3", this);
    findejeu_music = new Music("gameover_music.mp3");
    //initialiser le score
    score =new Score();
    sceneDeJeu->addItem(score);


    serp2 =NULL;
    serp = NULL;
    StageCourant = 1;
}

void Jeu::keyPressEvent(QKeyEvent *event)
{
    if(serp){
        serp->keyPressEvent(event);
    }else
        QGraphicsView::keyPressEvent(event);

}
void Jeu::afficherFin(QString titre, QString jouer)
{
    titreText = creertext(titre, "baloo 2", Qt::black);

    Button* joue = creerStg(jouer, 150, 40, titreText->boundingRect().width()/2 - 75, 170, 0, true, titreText);
    Button* quit = new Button("<< RETOUR", 150, 40, titreText);
    int rx = titreText->boundingRect().width()/2 - quit->boundingRect().width()/2;
    int ry = 220;
    quit->setPos(rx,ry);
    connect(quit, SIGNAL(clicked()), this, SLOT(routeurMenu()));

    Q_UNUSED(joue);
    Q_UNUSED(quit);

}
void Jeu::afficherMenu(QString titre, QString jouer)
{
    findejeu_music->stopMusic();
    background_music->stopMusic();
    menu_music->playMusic();

    background->setPixmap(QPixmap(":/bg/imageMenu.jpg").scaled(1200,600));
    sceneDeJeu->addItem(background);

    titreText = creertext(titre, "baloo 2", Qt::white);

    Button* menu = new Button("STAGES", 150,40, titreText);
    int mxPos = titreText->boundingRect().width()/2 - menu->boundingRect().width()/2 ;
    int myPos = 120;
    menu->setPos(mxPos,myPos);

    connect(menu, SIGNAL(clicked()), this, SLOT(afficherStages()));

    Button* joue = creerStg(jouer, 150, 40, titreText->boundingRect().width()/2 - 75, 170, 0, true, titreText);
    Button* quit = creerStg("QUIT", 150, 40, titreText->boundingRect().width()/2 - 75, 220, 0, false, titreText);

    Q_UNUSED(joue);
    Q_UNUSED(quit);

}

void Jeu::afficherStages()
{
    //supprimer les textes precedents
    titreText = textremove(titreText);

    //creer texte de stages menu
    stagesText = creertext("STAGES", font, Qt::white);

    //creer les bouttons des stages
    int x = 60;
    Button* stage = creerStg("1", 50, 50, 0,100, 1, true, stagesText);
    Button* stage2 = creerStg("2", 50, 50, x ,100, 2, true, stagesText);
    Button* stage3 = creerStg("3", 50, 50, 100,100, 3, true, stagesText);
    Button* stage4 = creerStg("4", 50, 50, 175,100, 4, true, stagesText);
    Button* stage5 = creerStg("5", 50, 50, 250,100, 5, true, stagesText);



    //bouuton de routeur
    Button* retour = new Button("<< RETOUR", 100, 50, stagesText);
    int rx = stagesText->boundingRect().width()/2 - retour->boundingRect().width()/2;
    int ry = 400;
    retour->setPos(rx,ry);
    connect(retour, SIGNAL(clicked()), this, SLOT(retourAffich()));

    //specifier les variables qu'il sont non utilise
    Q_UNUSED(stage);
    Q_UNUSED(stage2);
    Q_UNUSED(stage3);
    Q_UNUSED(stage4);
    Q_UNUSED(stage5);
}

void Jeu::afficherPause()
{
    //supprimer les textes precedents
    choixText = textremove(choixText);

    //creer le text de pause
    pauseText = creertext("PAUSE", "arial", Qt::white);

    //creer les boutons
    Button* commancer = new Button("COMMANCER", 150, 40, pauseText);
    commancer->setPos(100,140);
    connect(commancer, SIGNAL(clicked()), this, SLOT(commancer()) );
    Button* recommancer = creerStg("Recommancer", 150, 40, 100, 170, 0, true, pauseText);

    //bouton de routeur
    Button* routeur = new Button("<< RETOUR", 100, 50, pauseText);
    int rx = 20;
    int ry = 400;
    routeur->setPos(rx,ry);
    connect(routeur, SIGNAL(clicked()), this, SLOT(choix()) );

    Q_UNUSED(recommancer);
    Q_UNUSED(routeur);
}


void Jeu::debut()
{
    // controler la music
    menu_music->stopMusic();
    findejeu_music->stopMusic();
    background_music->playMusic();

    if(obs == NULL ){
    background->setPixmap(QPixmap(":/bg/blackbg.jpg").scaled(1200,600));
    sceneDeJeu->addItem(background);
    }

    //initialiser le serpent
    serp = new AnimerSerpent();
    serp->setFlag(QGraphicsItem::ItemIsFocusable);
    serp->setFocus();
    sceneDeJeu->addItem(serp);
    score->setVisible(true);
    score->setScore(0);

    //supprimer les precedents texts creer avant le debut du stage courant
    pauseText = textremove(pauseText);
    titreText = textremove(titreText);
    stagesText = textremove(stagesText);

    if(serp2) serp2->deleteLater();
    serp2 = serp;
}
void Jeu::finJeu()
{
    background_music->stopMusic();
    findejeu_music->playMusic();
    afficherFin("Fin De Jeu", "ReJeouer");
    sceneDeJeu->removeItem(serp);
    serp = NULL;
}

void Jeu::commancer()
{
    if(!serp->t->isActive()){
        serp->t->start(90);
        titreText = textremove(titreText);
        pauseText = textremove(pauseText);
    }

}
void Jeu::choix()
{
    //supprimer les textes precedents
    titreText = textremove(titreText);
    pauseText = textremove(pauseText);

    choixText = creertext("WARNING", "arial", Qt::white);

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
    stagesText = textremove(stagesText);
    titreText = textremove(titreText);

    background_music->stopMusic();
    afficherMenu("Jeu Serpent ", "Jouer");

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
    background_music->stopMusic();
    afficherMenu("Jeu Serpent ", "Jouer");
}


void Jeu::creerObs(int NumObs)
{
    //supprimer obstacles
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }

    //creer les obstacles
    if(NumObs != 0 && obs == NULL){
    obs = new Obstacles(NumObs);
    sceneDeJeu->addItem(obs);
    background->setPixmap(QPixmap(obs->bg).scaled(1200,600));
    background->setZValue(0);
    sceneDeJeu->addItem(background);
    }
    //debut de stage
    debut();
}

Button* Jeu::creerStg(QString text, int w, int h, int xpos, int ypos, int stg, bool debut, QGraphicsTextItem *pere)
{
    Button* button;
    if(stg != 0) {
        button = new Button(text, w, h, stg, pere);
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

void Jeu::stageSuiv()
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    creerObs(StageCourant);
}






QGraphicsTextItem* Jeu::textremove(QGraphicsTextItem *text)
{
    if(text != NULL){
        sceneDeJeu->removeItem(text);
        delete text;
        text = NULL;
    }
    return text;
}

QGraphicsTextItem *Jeu::creertext(QString titre, QString font, Qt::GlobalColor couleur)
{
    QGraphicsTextItem* text = new QGraphicsTextItem(titre);
    QFont titreFont(font, 50 );
    text->setFont(titreFont);
    text->setDefaultTextColor(couleur);
    int xPos = width()/2 - text->boundingRect().width()/2;
    int yPos = 100;
    text->setPos(xPos, yPos);
    sceneDeJeu->addItem(text);

    return text;
}

