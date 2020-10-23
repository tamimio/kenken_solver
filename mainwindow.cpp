#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

#include <sstream>
#include "KenKenSolver.h"

#include "QFileDialog"
#include "QMessageBox"  // error-window

#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGraphicsTextItem"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_graphicsScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_graphicsScene);

    prompt = m_graphicsScene->addText("Загрузите задание", QFont("Arial", 10) );

//    rects[0] = m_graphicsScene->addRect(0,0, 50,50, outlinePen, whiteBrush);
//    rects[1] = m_graphicsScene->addRect(0,50, 50,50, outlinePen, whiteBrush);
//    rects[2] = m_graphicsScene->addRect(0,100, 50,50, outlinePen, whiteBrush);

//    rects[3] = m_graphicsScene->addRect(50,0, 50,50, outlinePen, whiteBrush);
//    rects[4] = m_graphicsScene->addRect(50,50, 50,50, outlinePen, whiteBrush);
//    rects[5] = m_graphicsScene->addRect(50,100, 50,50, outlinePen, whiteBrush);

//    rects[6] = m_graphicsScene->addRect(100,0, 50,50, outlinePen, whiteBrush);
//    rects[7] = m_graphicsScene->addRect(100,50, 50,50, outlinePen, whiteBrush);
//    rects[8] = m_graphicsScene->addRect(100,100, 50,50, outlinePen, whiteBrush);



//    text[0] = m_graphicsScene->addText("3", QFont("Arial", 20) );
//    text[0]->setPos(0+14,0+4);
//    text[1] = m_graphicsScene->addText("3", QFont("Arial", 20) );
//    text[1]->setPos(0+14,50+4);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete[] rects;
}
void MainWindow::on_pushBtn_loadGame_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                tr("Открыть файл с задачей"), "./",
                "Текстовые файлы (*.txt)");

    try
    {
        KKSolver.readTask(filename);

        delete prompt;

        QBrush blueBrush(Qt::blue);
        QBrush greenBrush(Qt::green);
        QBrush whiteBrush(Qt::white);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);

        /* draw blank field */
        for (int i=0; i<KKSolver.getSize(); ++i)
            for (int j=0; j<KKSolver.getSize(); ++j)
                m_graphicsScene->addRect(i*50,j*50, 50,50, outlinePen, whiteBrush);
    }
    catch(/*std::pair<int,int>*/int pos)
    {
        QMessageBox messageBox;
//        std::string err;
//        sprintf(&err[0], "Ошибка чтения задания: строка %d", // столбец %d",
//                pos);//, pos[1]);
//        messageBox.critical(0,"Ошибка",&err[0]);
        messageBox.critical(0,"Ошибка","Ошибка чтения задачи");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::on_pushBtn_solveGame_clicked()
{
    try
    {
        KKSolver.solveTask();

        std::vector<std::vector<int> > matr = KKSolver.getField();

        /* fill field with results */
        for (int i=0; i<KKSolver.getSize(); ++i)
        {
            for (int j=0; j<KKSolver.getSize(); ++j)
            {
                char tmp = matr[j][i] + '0';
                QString qstr = QString::fromStdString(&tmp);
                m_graphicsScene->addText(qstr.left(1), QFont("Arial", 20))
                        ->setPos(50*i+14,j*50+4);
            }
        }
    }
    catch (...)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Сперва загрузите задание!");
        messageBox.setFixedSize(500,200);
    }
}
