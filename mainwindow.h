#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QGraphicsView"
#include <QMainWindow>
#include "dialog.h"
#include "fielddata.h"
#include "minesceens.h"
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    double sh,sw;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void deletold();
    void display();
    void display1(double ,double ,int ,int);
    bool JudgeIsWin();//判赢
      void block_blank(double px, double py, int x, int y);//一整块为空，全部翻起来，直到边缘为数字或遇到边
    void addnew();
private slots:
    void on_actionquit_triggered();
     void mousePressEvent(QMouseEvent *event);
    void on_actionconfig_triggered();

    void on_actionabout_triggered();

    void on_actionNew_game_triggered();

private:
    QGraphicsView* _view;
    mineSweepScene*_scene;
    Ui::MainWindow *ui;
    cellItem *_cItem;

};
#endif // MAINWINDOW_H
