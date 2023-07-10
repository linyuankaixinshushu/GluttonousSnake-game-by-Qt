#include "snake.h"
#include <QPainter>
#include <const.h>
extern const int TILE_SIZE;
static const int SNAKE_SIZE = 10;

Snake::Snake(GameController* controller) : controller(controller),
    speed(5),
    head(0,0),
    growing(4),
    moveDirection(NoMove)
{
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter -> save();
    painter -> fillPath(shape(),QBrush(Qt::green));
    painter -> restore();
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(QRectF(0,0,SNAKE_SIZE,SNAKE_SIZE));
    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), SNAKE_SIZE, SNAKE_SIZE));
    }
    return path;
}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (QPointF p, tail) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }
    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));
    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + SNAKE_SIZE,      // width
                          br.y() - tl.y() + SNAKE_SIZE       //height
                          );
    return bound;
}

void Snake::advance(int phase)
{
    if(phase == 0) {
        return ;
    }
    if((tickcount++) % speed != 0) {
        return ;
    }
    if(moveDirection == NoMove) {
        return ;
    }

    if (growing > 0) {
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        tail.takeFirst();
        tail << head;
    }

    switch (moveDirection) {
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
        default:
            break;
    }

    setPos(head);
    handleCollisions();
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if (head.rx() < -100) {
        head.rx() = 90;
    }
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    if (head.rx() >= 100) {
        head.rx() = -100;
    }
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if(head.ry() < -100) {
        head.ry() = 90;
    }
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if(head.ry() >= 100) {
        head.ry() = -100;
    }
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem* p, collisions) {
        if (p -> data(GD_Type) == GO_Food) {
            controller -> snakeAtFood((Food *)p);
            growing += 1;
        }
    }
    if(tail.contains(head)) {
        controller -> SnakeEatself();
    }
//    Qt::ContainsItemShape：如果被检测物的形状（shape()）完全包含在检测物内，算做碰撞；
//    Qt::IntersectsItemShape：如果被检测物的形状（shape()）与检测物有交集，算做碰撞；
//    Qt::IntersectsItemBoundingRect：如果被检测物的包含矩形（boundingRect()）与检测物有交集，算做碰撞。
//    Qt::ContainsItemBoundingRect：如果被检测物的包含矩形（boundingRect()）完全包含在检测物内，算做碰撞；
    //我们使用的是Intersectsitemshape 所以我们之前设置boudingrect大于实际范围是没有关系的！
}

void Snake::setMoveDirection(Snake::Direction direction)
{
    moveDirection = direction;
}

Snake::Direction Snake::getMoveDirection()
{
    return this -> moveDirection;
}
