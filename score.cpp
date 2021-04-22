#include "score.h"

#include <QFont>

Score::Score(QGraphicsItem* parent):QGraphicsTextItem(parent)
{
    score = 0;

    setPos(5,10);
    setFont(QFont("", 20));
    setDefaultTextColor(Qt::white);
    setZValue(6);

}
int Score::getScore()
{
    return score;
}

void Score::setScore(int valeur)
{
    score = valeur;
    setPlainText("Score: " + QString::number(score));
}


