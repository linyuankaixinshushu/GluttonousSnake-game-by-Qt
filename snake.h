#ifndef SNAKE_H
#define SNAKE_H
#include <QGraphicsItem>
#include <QList>
#include "gamecontroller.h"

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(GameController* controller);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void setMoveDirection(Direction);
    Direction getMoveDirection();
private:
    GameController* controller;
    QPointF head;
    int growing;
    int speed;
    int tickcount;
    QList<QPointF> tail;
    Direction moveDirection;

    void advance(int phase);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void handleCollisions();
};

#endif // SNAKE_H
