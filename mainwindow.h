#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QGraphicsScene;
class QGraphicsView;
class GameController;

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void adjustViewsize();
private:
    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *controller;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
