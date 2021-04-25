#include "score.h"

#include <QFont>
#include "jeu.h"

extern Jeu *jeu;

Score::Score(QGraphicsItem* parent):QGraphicsTextItem(parent)
{

    score = 0;
    setZValue(6);
}
int Score::getScore()
{
    return score;
}

void Score::setScore(int valeur)
{
    score = valeur;
    //
}

void Score::afficherScore()
{
    titre = "Score: " + QString::number(getScore());
    scoreText = new QGraphicsTextItem(titre);
    scoreText->setFont(QFont("baloo 2", 50));
    scoreText->setPos(100,250);
    scoreText->setDefaultTextColor(Qt::white);
    jeu->sceneDeJeu->addItem(scoreText);
}


