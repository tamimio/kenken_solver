#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "KenKenSolver.h"
#include "QGraphicsScene"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    KenKenSolver * KKSolver;            /* solver */
    QGraphicsScene * m_graphicsScene;   /* scene */
    QGraphicsTextItem * prompt;         /* welcome text */

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawField(); /* draws puzzle field basing on size and rules in KKSolver */
    void fillField(std::vector<std::vector<int> > & matr); /* fills field with given matrix */

private slots:
    void on_pushBtn_loadGame_clicked();
    void on_pushBtn_solveGame_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
