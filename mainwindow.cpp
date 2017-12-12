#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMenu *mFile = new QMenu("File");
        QAction *msgSave = mFile->addAction("Save");
        QAction *msgExit = mFile->addAction("Exit");

        connect(msgSave,  SIGNAL(triggered()), this, SLOT(on_save_triggered()));
        connect(msgExit,  SIGNAL(triggered()), this, SLOT(on_exit_triggered()));

    menuBar()->addMenu(mFile);

    QToolBar *bFile=new QToolBar();
        QAction *kohan = bFile->addAction("Kohan");
        QAction *hoar = bFile->addAction("Hoar");
        QAction *triangle = bFile->addAction("Triangle");
        QAction *gilbert = bFile->addAction("Gilbert");
        QAction *tree1 = bFile->addAction("Tree1");
        QAction *tree2 = bFile->addAction("Tree2");
        QAction *tree3 = bFile->addAction("Tree3");
        connect(kohan, SIGNAL(triggered()), SLOT(on_kohan_clicked()));
        connect(hoar, SIGNAL(triggered()), SLOT(on_hoar_clicked()));
        connect(triangle, SIGNAL(triggered()), SLOT(on_triangle_clicked()));
        connect(gilbert, SIGNAL(triggered()), SLOT(on_gilbert_clicked()));
        connect(tree1, SIGNAL(triggered()), SLOT(on_tree1_clicked()));
        connect(tree2, SIGNAL(triggered()), SLOT(on_tree2_clicked()));
        connect(tree3, SIGNAL(triggered()), SLOT(on_tree3_clicked()));

        addToolBar(Qt::TopToolBarArea, bFile);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter *painter;
    painter->setPen(QPen(Qt::black,6));
    painter->drawLine(QPoint(xss,yss),QPoint(xee,yee));

}

void MainWindow::DrawLine(int xs, int ys, int xe, int ye)
{
    xss = xs;
    yss = ys;
    xee = xe;
    yee = ye;
    this->update();
}

void MainWindow::factor()
{
    char left;
    QList<char> *right = new QList<char>;
    QList<Rule> *rule = new QList<Rule>;
    char equal = '=';
    char comma = ',';
    char F = 'F';
    char plus = '+';
    char minus = '-';
    char open = '[';
    char close = ']';

    for(int i = 0; i < 11;i++)
    {
        if(rules[i] == equal)
        {
            left = rules[i-2];
            i += 2;
            while(rules[i] != comma && i < 11)
            {
                right->append(rules[i]);
                if(i == 11)
                    break;
                else
                    i++;
            }
            rule->append(*(new Rule(&left,right)));
            i++;
        }
        right->clear();
    }

    QList<char> *axiom = new QList<char>;

    for (int i = 0; i < axiom->length(); i++)
    {
        axiom->append(axioma[i]);
    }

    for (int i = 0; i < depth; i++)
    {
        for (int j = 0; j < axiom->count(); j++)
        {
            for (int k = 0; k < rule->count(); k++)
            {
                if (axiom->at(j) == rule->at(l).left)
                {
                    axiom->removeAt(j);
                    for (int l = 0; l < rule->at(k).right->count(); l++)
                    {
                        axiom->insert(j, rule->at(k).right->at(l)); j++;
                    }
                    j--;
                    break;
                }
            }
        }
    }

    double ang = 0;
    int xstart = this->width() / 2;
    int ystart = this->height() / 2;
    if (type == 5)
    {
        ang = 3 * 3.14 / 2; ystart = this->height() / 4 * 3;
    }
    QStack<int> *xremembered = new QStack<int>();
    QStack<int> *yremembered = new QStack<int>();
    QStack<double> *anremembered = new QStack<double>();
    for(int i = 0; i < axiom->count(); i++)
    {
        if (axiom->at(i) == F)
        {
            int xend = xstart + int(qCos(ang) * step);
            int yend = ystart + int(qSin(ang) * step);
            this->DrawLine(xstart, ystart, xend, yend);
            xstart = xend; ystart = yend;
        }
        if (axiom->at(i) == plus)
        {
            ang += angle;
        }
        if (axiom->at(i) == minus)
        {
            ang -= angle;
        }
        if (axiom->at(i) == open)
        {
            xremembered->push(xstart);
            yremembered->push(ystart);
            anremembered->push(ang);
        }
        if (axiom->at(i) == close)
        {
            xstart = xremembered->pop();
            ystart = yremembered->pop();
            ang = anremembered->pop();
        }
    }
}

void MainWindow::on_kohan_clicked()
{
    axioma = new char[7];
    axioma[0]='F';axioma[1] = '+';axioma[2] = '+';
    axioma[3]='F';axioma[4] = '+';axioma[5] = '+';axioma[6]='F';
    rules = new char[12];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]='-';rules[6]='F';rules[7]='+';rules[8]='+';rules[9]='F';rules[10]='-';rules[11]='F';
    angle = 60;
    step = 2;
    depth = 4;
    factor();
    type = 1;
}

void MainWindow::on_hoar_clicked()
{
    axioma = new char [2];
    axioma[0]='F';axioma[1]='X';
    rules = new char[27];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]=',';rules[6]=' ';rules[7]='X';rules[8]=' ';rules[9]='=';rules[10]=' ';rules[11]='X';
    rules[12]='+';rules[13]='Y';rules[14]='F';rules[15]='+';rules[16]=',';rules[17]=' ';rules[18]='Y';
    rules[19]=' ';rules[20]='=';rules[21]=' ';rules[22]=' -';rules[23]='F';rules[24]='X';rules[25]='-';
    rules[26]='Y';
    angle = 90;
    step = 2;
    depth = 12;
    factor();
    type = 2;
}

void MainWindow::on_triangle_clicked()
{
    axioma =new char[11];
    axioma[0]='F';axioma[1] = 'X';axioma[2] = 'F';
    axioma[3]='-';axioma[4] = '-';axioma[5] = 'F';axioma[6]='F';
    axioma[7]='F';axioma[8] = 'F';axioma[9] = '-';axioma[10]='-';
    axioma[11]='F';axioma[12] = 'F';
    rules = new char[22];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]='-';rules[6]='-';rules[7]='F';rules[8]='X';rules[9]='F';rules[10]='+';rules[11]='+';
    rules[12]='F';rules[13]='X';rules[14]='F';rules[15]='+';rules[16]='+';rules[17]='F';rules[18]='X';
    rules[19]='F';rules[20]='-';rules[21]='-';
    angle = 60;
    step = 2;
    depth = 6;
    factor();
    type = 3;
}

void MainWindow::on_gilbert_clicked()
{
    axioma = new char[1];axioma[0]= 'X';
    rules = new char[38];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]=',';rules[6]=' ';rules[7]='X';rules[8]=' ';rules[9]='=';rules[10]=' ';rules[11]='-';
    rules[12]='Y';rules[13]='F';rules[14]='+';rules[15]='X';rules[16]='F';rules[17]='X';rules[18]='+';
    rules[19]='F';rules[20]='Y';rules[21]='-';rules[22]=',';rules[23]=' ';rules[24]='Y';rules[25]=' ';
    rules[26]='=';rules[27]=' ';rules[28]='+';rules[29]='X';rules[30]='F';rules[31]='- ';rules[32]='Y';
    rules[32]='F';rules[33]='Y';rules[34]='-';rules[35]='F';rules[36]='X';rules[37]='+';
    angle = 90;
    step = 3;
    depth = 6;
    factor();
    type = 4;
}

void MainWindow::on_tree1_clicked()
{
    axioma = new char[1];axioma[0] = 'F';
    rules = new char[15];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]='[';rules[6]='+';rules[7]='F';rules[8]=']';rules[9]='F';rules[10]='[';rules[11]='-';
    rules[12]='F';rules[13]=']';rules[14]='F';
    angle = 26;
    step = 3;
    depth = 6;
    factor();
    type = 5;
}

void MainWindow::on_tree2_clicked()
{
    axioma = new char[1];axioma[0] = 'F';
    rules = new char[17];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]='[';rules[6]='+';rules[7]='F';rules[8]=']';rules[9]='F';rules[10]='[';rules[11]='-';
    rules[12]='F';rules[13]=']';rules[14]='[';rules[15]='F';rules[16]=']';
    angle = 20;
    step = 3;
    depth = 6;
    factor();
    type = 5;
}

void MainWindow::on_tree3_clicked()
{
    axioma = new char[1];axioma[0] = 'X';
    rules = new char[19];
    rules[0] = 'F';rules[1] = ' ';rules[2] = '=';rules[3]=' ';rules[4]='F';
    rules[5]='F';rules[6]=',';rules[7]=' ';rules[8]='X';rules[9]=' ';rules[10]='=';rules[11]=' ';
    rules[12]='F';rules[13]='[';rules[14]='+';rules[15]='X';rules[16]=']';rules[17]='F';
    rules[18]='X';
    angle = 26;
    step = 3;
    depth = 6;
    factor();
    type = 5;
}
