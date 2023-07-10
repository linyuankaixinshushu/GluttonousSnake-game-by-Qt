#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "gamecontroller.h"
extern const int TILE_SIZE;

void MainWindow::adjustViewsize()
{
    view -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene -> setSceneRect(-100,-100,200,200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE,TILE_SIZE);//设置一个大小为TILE_SIZE*TILE_SIZE的空图片
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));//用灰色填充整个图片
    p.drawRect(0,0,TILE_SIZE,TILE_SIZE);
    view -> setBackgroundBrush(QBrush(bg));//用这个图片作为view的背景，画刷会复制
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene,this)),
      controller(new GameController(scene,this))
{
    setCentralWidget(view);
    setFixedSize(202,202);
    initScene();
    initSceneBackground();

    QTimer::singleShot(0,this,&MainWindow::adjustSize);
    //等到绘制事件完成才执行槽函数，而不是直接调用
}

MainWindow::~MainWindow()
{

}
