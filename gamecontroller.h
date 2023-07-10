#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "food.h"
#include "snake.h"

class Snake;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene *, QObject*);
    void snakeAtFood(Food *);
    void SnakeEatself();
protected:
    bool eventFilter(QObject *watched,QEvent* event);
private:
    QTimer timer;
    QGraphicsScene* scene;
    Snake* snake;

    void addNewFood();
    void handleKeyPressed(QKeyEvent* event);
private slots:
      void Gameover();
//    void pause();
//    void resume();
};

#endif // GAMECONTROLLER_H
