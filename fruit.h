#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsPixmapItem>
#include <QString>

class Fruit : public QGraphicsPixmapItem
{
public:
    Fruit(QString name = "" ,QGraphicsItem* parent=0);
    int score;
};

#endif // FRUIT_H
