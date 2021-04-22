#ifndef SERPPART_H
#define SERPPART_H

#include <QGraphicsPixmapItem>

class SerpPart :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    SerpPart(QGraphicsItem* parent=0);

    SerpPart* Preced();
    void setPreced(SerpPart* valeur);

    SerpPart* Suiv();
    void setSuiv(SerpPart* valeur);

    QString Direction();
    void setDirection(QString valeur);

    void move();
    void ajouterDerrier();
    void checkCollidingObject();

    QString part;
    void setImage();

    QString image;
    void setImage(QString valeur);
    int pas;
    int l=5;

private:
    SerpPart* suiv;
    SerpPart* preced;
    QString direction;
signals :
    void manger();
    void mangerF();
};

#endif // SERPPART_H
