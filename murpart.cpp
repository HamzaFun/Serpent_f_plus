#include "murpart.h"

MurPart::MurPart(QString mur, QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    murtype = "mur.png";
    if(mur != NULL)
        murtype = mur;

    setPixmap(QPixmap(":/images/"+murtype).scaled(40,40));
    setPos(0,0);
    setZValue(5);
}
