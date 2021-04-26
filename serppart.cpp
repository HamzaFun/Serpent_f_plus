#include "serppart.h"
#include "fruit.h"
#include "jeu.h"
#include "murpart.h"
#include <QList>
#include <QDebug>
#include <QMediaPlayer>

extern Jeu* jeu;

SerpPart::SerpPart(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
, image("2")
, pas(40)
{
    setZValue(1);
}

SerpPart *SerpPart::Preced()
{
    return preced;
}

void SerpPart::setPreced(SerpPart *valeur)
{
    preced = valeur;
}

SerpPart *SerpPart::Suiv()
{
    return suiv;
}

void SerpPart::setSuiv(SerpPart *valeur)
{
    suiv = valeur;
}

QString SerpPart::Direction()
{
    return direction;
}

void SerpPart::setDirection(QString valeur)
{
    direction = valeur;
}

void SerpPart::move()
{
    static int premier;
    if(direction == "DOWN"){
        this->setY(this->y()+pas);
    } else if(direction == "UP")
        this->setY(this->y()-pas);
    else if(direction == "LEFT")
        this->setX(this->x()- pas);
    else if(direction == "RIGHT")
        this->setX(this->x()+pas);
    if(premier){
        if(this->y() >= 600){
            this->setY(0);
        }
        else if(this->y() < 0){
            this->setY(600);
        }
        else if(this->x() < 0){
            this->setX(1200);
        }
        else if(this->x() >= 1200){
            this->setX(0);
        }
    }
    premier++;
    if(this->Suiv()!= NULL)
        direction = this->Suiv()->direction;
    if(part == "HEAD")
        checkCollidingObject();
    setImage();
}

void SerpPart::ajouterDerrier()
{
    int x,y;
    x=y=0;
    if(this->Suiv()->Direction() == "UP"){
        x = this->Suiv()->x();
        y = this->Suiv()->y()+ 40;
    }
    else if(this->Suiv()->Direction() == "DOWN"){
        x = this->Suiv()->x();
        y = this->Suiv()->y()- 40;
    }
    else if(this->Suiv()->Direction() == "RIGHT"){
        x = this->Suiv()->x()- 40;
        y = this->Suiv()->y();
    }
    else if(this->Suiv()->Direction() == "LEFT"){
        x = this->Suiv()->x()+ 40;
        y = this->Suiv()->y();
    }
    setPos(x,y);
}

void SerpPart::checkCollidingObject()
{
    QList <QGraphicsItem* > coll = this->collidingItems();

//
    for(int i = 0, n = coll.length(); i< n; ++i){
        Fruit* f = dynamic_cast<Fruit *>(coll[i]);
        if(f) {
            QPointF thisCenter(x()+10,y()+10);
            QPointF foodCenter(f->x()+10,f->y()+10);
            QLineF ln(thisCenter,foodCenter);
            if(ln.length() == 0){

                jeu->serp->ajoutePart(); 
                jeu->sceneDeJeu->removeItem(f);
                jeu->score->setScore(jeu->score->getScore()+ f->score);
                delete f;
                if(jeu->score->getScore() == l){
                    emit jeu->sfx->coin2();
                    emit mangerF();
                    l += 5;
                }else{
                    emit jeu->sfx->coin1();
                    emit manger();
                }
                if(jeu->obs != NULL){

                    if(jeu->obs->maxScore <= jeu->score->getScore()){
                        qDebug() << "next stage";
                        jeu->StageCourant++;
                        emit finStage();
                    }
                }
            }
        }
        else if(coll[i]) {
            if(typeid(*coll[i])== typeid(SerpPart) || typeid(*coll[i]) == typeid (MurPart))
                jeu->finJeu();

            return;

        }
    }
}

void SerpPart::setImage()
{
    if(part == "HEAD"){

        if(direction == "UP"){
          setPixmap(QPixmap(QString(":/skins/%1headup.png").arg(image)).scaled(40,40));
        }else if(direction == "DOWN"){
           setPixmap(QPixmap(QString(":/skins/%1headDown.png").arg(image)).scaled(40,40));
        }else if(direction == "LEFT"){
            setPixmap(QPixmap(QString(":/skins/%1headLeft.png").arg(image)).scaled(40,40));
        }else if(direction == "RIGHT"){
            setPixmap(QPixmap(QString(":/skins/%1head.png").arg(image)).scaled(40,40/*,Qt::KeepAspectRatio*/));
        }
        setZValue(2);

    }
    else if(part == "TAIL") {
        if(direction == "UP"){
          setPixmap(QPixmap(QString(":/skins/%1tailUp.png").arg(image)).scaled(40,40));
        }else if(direction == "DOWN"){
           setPixmap(QPixmap(QString(":/skins/%1tailDown.png").arg(image)).scaled(40,40));
        }else if(direction == "LEFT"){
            setPixmap(QPixmap(QString(":/skins/%1tailLeft.png").arg(image)).scaled(40,40));
        }else if(direction == "RIGHT"){
            setPixmap(QPixmap(QString(":/skins/%1tail.png").arg(image)).scaled(40,40));
        }
    }
    else if (part == "PART"){
        if(direction == this->Preced()->Direction()){
        if(direction == "LEFT" ||direction ==  "RIGHT")
            setPixmap(QPixmap(QString(":/skins/%1left-right.png").arg(image)).scaled(40,40));
        else if (direction == "UP" || direction == "DOWN")
            setPixmap(QPixmap(QString(":/skins/%1up-down.png").arg(image)).scaled(40,40));
        }
        else{
            if((direction == "UP" && this->Preced()->Direction() == "LEFT")
                    || (direction == "RIGHT" && this->Preced()->Direction() == "DOWN"))
                setPixmap(QPixmap(QString(":/skins/%1leftUp-downRight.png").arg(image)).scaled(40,40));
            else if((direction == "UP" && this->Preced()->Direction() == "RIGHT")
                    || (direction == "LEFT" && this->Preced()->Direction() == "DOWN"))
                setPixmap(QPixmap(QString(":/skins/%1rightUp-downLeft.png").arg(image)).scaled(40,40));
            else if((direction == "LEFT" && this->Preced()->Direction() == "UP")
                    || (direction == "DOWN" && this->Preced()->Direction() == "RIGHT"))
                setPixmap(QPixmap(QString(":/skins/%1upLeft-rightDown.png").arg(image)).scaled(40,40));
            else
                setPixmap(QPixmap(QString(":/skins/%1upRight-leftDown.png").arg(image)).scaled(40,40));

        }

    }
}

















