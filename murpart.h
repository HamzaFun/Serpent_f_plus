#ifndef MURPART_H
#define MURPART_H

#include <QGraphicsPixmapItem>

class MurPart : public QGraphicsPixmapItem
{
public:
    MurPart(QString mur, QGraphicsItem* parent= 0);

    QString murtype;
};

#endif // MURPART_H
