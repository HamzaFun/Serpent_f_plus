#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QObject>

class Button :public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum class Niveau{
        facile, difficile, normale, invalid
    };
    Button(QString name,int width, int height, QGraphicsItem * parent = NULL);
    Button(QString name,int width, int height,int stg, QGraphicsItem * parent = NULL);
    Button(QString name,int width, int height,Niveau niveau, QGraphicsItem* parent);

    QGraphicsPixmapItem* locke = NULL;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void deletelock();
    void setHoverd();
    int stgNum ;
    Button::Niveau niveau;
signals:
    void clicked();
    void clicked(int);
    void clicked(Button::Niveau);
private:
    QGraphicsTextItem* text;
    int width;
    int height;
};

#endif // BUTTON_H
