#include "gamecontroller.h"
#include "food.h"
#include <QEvent>
#include "snake.h"
#include "QMessageBox"

GameController::GameController(QGraphicsScene* scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(this))
{
    timer.start(1000/33);
    Food *a1 = new Food(0,-50);
    scene -> addItem(a1);
    scene -> addItem(snake);
    scene -> installEventFilter(this);
    connect(&timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
}

void GameController::snakeAtFood (Food * food)
{
    scene -> removeItem(food);
    delete food;
    addNewFood();
}

void GameController::SnakeEatself()
{
    QTimer::singleShot(0,this,&Gameover);
}

bool GameController::eventFilter(QObject *watched, QEvent *event)
{
    if (event -> type() == QEvent::KeyPress){
        handleKeyPressed((QKeyEvent*) event);
        return true;
    }
    else {
        return QObject::eventFilter(watched,event);
    }
}

    void GameController::addNewFood()
    {
        int x, y;
        do {
            x = (int) (qrand() % 100) / 10;
            y = (int) (qrand() % 100) / 10;
            x *= 10;
            y *= 10;
        } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));
        Food *food = new Food(x , y);
        scene -> addItem(food);
    }

void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            if(snake -> getMoveDirection() != Snake::MoveRight)
            snake->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            if(snake -> getMoveDirection() != Snake::MoveLeft)
            snake->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            if(snake -> getMoveDirection() != Snake::MoveDown)
            snake->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            if(snake -> getMoveDirection() != Snake::MoveUp)
            snake->setMoveDirection(Snake::MoveDown);
            break;
    }
}

void GameController::Gameover()
{
    delete snake;
    disconnect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
        if (QMessageBox::Yes == QMessageBox::information(NULL,
                                tr("Game Over"), tr("Again?"),
                                QMessageBox::Yes | QMessageBox::No,
                                QMessageBox::Yes)) {
            connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
            scene -> clear();

            snake = new Snake(this);
            scene -> addItem(snake);
            addNewFood();
        } else {
            exit(0);
        }
}

//void GameController::pause()
//{
//    disconnect(&timer,&QTimer::timeout,scene,);
//}

//void GameController::resume()
//{
//    connect(&timer,&QTimer::timeout,scene,&QGraphicsItem::advance);
//    //定时器时间用尽时触发timeout信号，advance调用所有图片对象的advance
//}


