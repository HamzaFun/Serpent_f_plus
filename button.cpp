#include "button.h"

#include <QBrush>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QPen>

Button::Button(QString name,int width, int height, QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    stgNum = 0;
    setRect(0,0,width,height);
    QBrush brush;
    QFont font;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#240b36"));
    setBrush(brush);
    font.setBold(true);
    font.setWeight(100);

    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);

    text->setFont(font);
    setAcceptHoverEvents(true);
}
Button::Button(QString name,int width, int height, int stg, QGraphicsItem* parent):QGraphicsRectItem(parent)
{
    stgNum = stg;
    setRect(0,0,width,height);
    QBrush brush;
    QFont font;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#240b36"));
    setBrush(brush);
    font.setBold(true);
    font.setWeight(100);


    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);

    text->setFont(font);
    setAcceptHoverEvents(true);
    locke = new QGraphicsPixmapItem(this);
    locke->setPixmap(QPixmap(":/svgs/lock.png").scaled(30,30,Qt::KeepAspectRatio));
    locke->setPos(pos().x()+15, pos().y()+15);
    locke->setZValue(10);

}
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    {
        emit clicked(stgNum);
        emit clicked();
    }

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#240bf6"));
    setPen(QPen(Qt::green));
    setCursor(QCursor(Qt::PointingHandCursor));
    setBrush(brush);
    }
}


void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#240b36"));
    setPen(QPen(Qt::NoPen));

    setBrush(brush);
    }
}

void Button::deletelock()
{
    if(locke != NULL){
    delete locke;
    locke = NULL;
    }
}

void Button::setHoverd()
{
    if(locke != NULL){
    setOpacity(80);
    setAcceptedMouseButtons(Qt::NoButton);
    setAcceptHoverEvents(false);
    }
    else{
        setOpacity(100);
        setAcceptedMouseButtons(Qt::AllButtons);
        setAcceptHoverEvents(true);
        deletelock();
    }
}

