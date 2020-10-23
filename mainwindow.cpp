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
}

MainWindow::~MainWindow()
{
    delete ui;
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

        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        QColor colour;
        colour.setHsv(210,128,200);
        brush.setColor(colour);

        std::pair <std::vector<QString>, std::vector<std::vector<int> > > p;
       p = KKSolver.getRules();
       p.first;
       p.second;
       std::vector<int>::iterator it = std::find(p.second[0].begin(), p.second[0].end(), 3);
       int index = std::distance(p.second[0].begin(), it);
        /* draw blank field */
       int k=0;
        for (int i=0; i<KKSolver.getSize(); ++i)
            for (int j=0; j<KKSolver.getSize(); ++j)
            {

                for(int z=0; i<p.second.size(); ++z)
                {
                    if (std::find(p.second[z].begin(), p.second[z].end(), k)
                            !=p.second[z].end())
                    {
                        // z -number of rule
                        colour.setHsv(z*((int)255/p.first.size()),128,200);
                        break;
                    }

                }


                //colour.setHsv(i*25+j*25,128,200);
                brush.setColor(colour);
                m_graphicsScene->addRect(j*50,i*50, 50,50,
                                         outlinePen, brush); /*QBrush(Qt::white)*/
                            k++;
            }
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
