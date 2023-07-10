#ifndef FOOD_H
#define FOOD_H
#include "const.h"
#include <QGraphicsItem>



class Food : public QGraphicsItem
{
public:
    Food(double x, double y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;
};

#endif // FOOD_H
