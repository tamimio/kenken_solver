#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "KenKenSolver.h"

//#include "QGraphicsScene"
//#include "QGraphicsView"
#include "QGraphicsTextItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    KenKenSolver KKSolver;
    QGraphicsScene * m_graphicsScene;
    QGraphicsTextItem * prompt;

private slots:
    void on_pushBtn_loadGame_clicked();

    void on_pushBtn_solveGame_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
