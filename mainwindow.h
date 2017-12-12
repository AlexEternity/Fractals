#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QGraphicsView>
#include <QPixmap>
#include <rule.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void factor();
    void DrawLine(int xs,int ys,int xe,int ye);

signals:
    void signal1(QString f);

public slots:
    void on_kohan_clicked();
    void on_hoar_clicked();
    void on_triangle_clicked();
    void on_gilbert_clicked();
    void on_tree1_clicked();
    void on_tree2_clicked();
    void on_tree3_clicked();

protected:
    void paintEvent(QPaintEvent *);

private:
    char *axioma;
    char *rules;
    double angle;
    int step;
    int depth;
    int type;
    int xss;
    int xee;
    int yss;
    int yee;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
