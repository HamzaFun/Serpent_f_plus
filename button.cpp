#include "button.h"

#include <QBrush>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QPen>

Button::Button(QString name,int width, int height, QGraphicsItem* parent):QGraphicsRectItem(parent)
{

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

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    {
//        if(stgNum != 0) emit clicked(stgNum);
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

