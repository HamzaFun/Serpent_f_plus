#include "murpart.h"

MurPart::MurPart(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/mur.png").scaled(40,40));
    setPos(0,0);
    setZValue(5);
}
