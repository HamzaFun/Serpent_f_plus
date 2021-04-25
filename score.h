#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(QGraphicsItem* parent = 0);
    int getScore();
    void setScore(int valeur);
    void afficherScore();
    QString titre;

    QGraphicsTextItem* scoreText = NULL;

private :
    int score;
};

#endif // SCORE_H
