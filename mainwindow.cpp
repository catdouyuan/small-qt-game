#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QGraphicsView"
#include "minesceens.h"
#include "fielddata.h"
#include <queue>
struct Point_Px
{
    double px;
    double py;
};
int remainminenum=Field->getmine();
int total=Field->getheight()*Field->getwide();
double factor_Scale=0.9;//缩放因子(自定义),其实最后限制30*19了，这个缩放因子在14寸以上屏幕不会用到。
bool IsScale=false;//是否缩放(缩放了的话鼠标坐标也要缩放)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fielddata::getInstance();

    _view = new QGraphicsView;
    this->setCentralWidget(_view);

   _scene=new mineSweepScene;
    _view->setScene(_scene);
     this->showMaximized();//最大化窗口
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionquit_triggered()
{
    qApp->quit();
}


void MainWindow::on_actionconfig_triggered()
{
    Dialog  mydialog(Field->getheight(),Field->getwide(),Field->getmine());
    if(mydialog.exec()==QDialog::Accepted){
        if(mydialog._minenum<mydialog._height*mydialog._wide*0.5){
            deletold();
            Field->customize(mydialog._height,mydialog._wide,mydialog._minenum);

            Field->reset();
            addnew();
        }
        else {
               QMessageBox::warning(this,"Warning","mines too many!");
        }
    }
}


void MainWindow::on_actionabout_triggered()
{
    QMessageBox::information(this,"about","version 1.0");
}
void MainWindow::deletold(){
    this->showMaximized();
    if(this->width()<_scene->width()){
        _view->scale(_scene->width()/this->width()/factor_Scale,_scene->height()/this->height()/factor_Scale);
        IsScale=false;
    }
    if(!_scene){
        delete _scene;
        _scene=nullptr;
    }
}
void MainWindow::addnew(){
    _scene=new mineSweepScene;
    _view->setScene(_scene);
    this->showMaximized();
    if(this->width()<_scene->width()){
        IsScale=true;
        _view->scale(this->width()/_scene->width()*factor_Scale,this->height()/_scene->height()*factor_Scale);

    }
    else {
        IsScale=false;
    }
    remainminenum=Field->getmine();
    total=Field->getheight()*Field->getwide();
}

void MainWindow::on_actionNew_game_triggered()
{
        deletold();
    Field->customize(Field->getheight(),Field->getwide(),Field->getmine());
        Field->reset();
    addnew();
}
void MainWindow:: mousePressEvent(QMouseEvent *event){
     double px=event->localPos().x();
     double py=event->localPos().y();
     QGraphicsItem *item =_view->itemAt(px, py-35);
     _cItem=dynamic_cast<cellItem*>(item);
     if(item){
         static double cw = IsScale ?  item->boundingRect().width()*this->width()/_scene->width()*factor_Scale : item->boundingRect().width();
         static double ch = IsScale ?  item->boundingRect().height()*this->width()/_scene->width()*factor_Scale : item->boundingRect().height();
         switch(event->button()){
             case  Qt::LeftButton:
             if(INITSTSTUS==_cItem->getStatus()||QUESTION==_cItem->getStatus()){
                     switch(Field->_field[item->pos().x()/cw][item->pos().y()/ch]){
                 case -1:
                         --total;
                         _cItem->setstatus(EXPLORE);
                        // display1(px,py,item->pos().x()/cw,item->pos().y()/ch);
                         _scene->scenedisplay();
                         QMessageBox::information(this,"Result","You lost! New game will start...");
                         on_actionNew_game_triggered();
                         break;
                 case 0:
                     _cItem->setstatus(BLANK);
                     --total;
                     JudgeIsWin();
                      block_blank(px,py,item->pos().x()/cw,item->pos().y()/ch);
                     break;
                 case 1:
                     _cItem->setstatus(DIGITAL,1);
                     --total;JudgeIsWin();
                       break;
                 case 2:
                     _cItem->setstatus(DIGITAL,2);
                     --total;JudgeIsWin();
                       break;
                 case 3:
                     _cItem->setstatus(DIGITAL,3);
                     --total;JudgeIsWin();
                       break;
                 case 4:
                     _cItem->setstatus(DIGITAL,4);
                     --total;JudgeIsWin();
                       break;
                 case 5:
                     _cItem->setstatus(DIGITAL,5);
                     --total;JudgeIsWin();
                       break;
                 case 6:
                     _cItem->setstatus(DIGITAL,6);
                     --total;JudgeIsWin();
                       break;
                 case 7:
                     _cItem->setstatus(DIGITAL,7);
                     --total;JudgeIsWin();
                       break;
                 case 8:
                     _cItem->setstatus(DIGITAL,8);
                     --total;JudgeIsWin();
                       break;
                 default:break;
                     }

             } else if(FLAG==_cItem->getStatus()){//插旗位置只能通过右键解锁
                 ;
             }
             break;
              case Qt::RightButton:
             if(INITSTSTUS==_cItem->getStatus()){
                 _cItem->setstatus(FLAG);
                 if(-1==Field->_field[item->pos().x()/cw][item->pos().y()/ch]){
                     --remainminenum;;JudgeIsWin();

                 }
             }
             else if(FLAG==_cItem->getStatus()){
                 _cItem->setstatus(QUESTION);
                 if(-1==Field->_field[item->pos().x()/cw][item->pos().y()/ch]){
                     ++remainminenum;
                 }

             }
             else if(QUESTION==_cItem->getStatus()){
                 _cItem->setstatus(INITSTSTUS);
             }
             break;
             default:
                 break;
         }
     }
}
void MainWindow::block_blank(double px, double py, int x, int y){
    Field->initvisit();

    QGraphicsItem *item =_view->itemAt(px, py-35);

    static double cw = IsScale ?  item->boundingRect().width()*this->width()/_scene->width()*factor_Scale : item->boundingRect().width();
    static double ch = IsScale ?  item->boundingRect().height()*this->width()/_scene->width()*factor_Scale : item->boundingRect().height();
    sh=ch,sw=cw;
    const int dir[8][2]={{0, 1}, {1, 0}, {0, -1}, {-1, 0},//下,右,上,左
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}//右下,右上,左上,左下
    };//八个方向可以扩展

    queue<pair<Point_Px,int>> que;//保存鼠标坐标和数据矩阵坐标
    que.push(pair<Point_Px,int>({px,py},x*Field->getheight()+y));
    Field->_visited[x][y]=1;
    while(!que.empty()){
        pair<Point_Px,int> fr=que.front();
        que.pop();
        px=fr.first.px;
        py=fr.first.py;
        x=fr.second/Field->getheight();
        y=fr.second%Field->getheight();

        for(int i=0;i<8;++i){//8个方向扩展
            double npx=px+cw*dir[i][0];
            double npy=py+ch*dir[i][1];
            int nx=x+dir[i][0];
            int ny=y+dir[i][1];
            //超出边界判断
            //qDebug()<<npx<<npy<<nx<<ny;
            if(nx<0 || nx>=Field->getwide() || ny<0 || ny>=Field->getheight()
                || 1==Field->_visited[nx][ny]){
                //qDebug()<<"miaomiao-continue";
                continue;
            }

            item =_view->itemAt(npx, npy-35);
            _cItem=dynamic_cast<cellItem*>(item);

            //插旗的不再寻路
            if(FLAG==_cItem->getStatus())
                continue;

            //如果数字为0，表示周围没有雷，则继续加入队列进行下去
            if(0==Field->_field[nx][ny]){
                --total;JudgeIsWin();
                que.push(pair<Point_Px,int>({npx,npy},nx*Field->getheight()+ny));
                Field->_visited[nx][ny]=1;
                _cItem->setstatus(BLANK);
            }
            else{
                switch (Field->_field[nx][ny]) {
                case 1:
                    if(_cItem->getStatus()!=DIGITAL){//注意需要加上状态判断，不然会再次设置相同状态，浪费资源，且把状态个数减去1，造成计算错误
                        _cItem->setstatus(DIGITAL,1);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding has 1 mine."<<endl;
                    break;
                case 2:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,2);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 2 mines."<<endl;
                    break;
                case 3:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,3);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 3 mines."<<endl;
                    break;
                case 4:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,4);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 4 mines."<<endl;
                    break;
                case 5:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,5);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 5 mines."<<endl;
                    break;
                case 6:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,6);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 6 mines."<<endl;
                    break;
                case 7:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,7);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 7 mines."<<endl;
                    break;
                case 8:
                    if(_cItem->getStatus()!=DIGITAL){
                        _cItem->setstatus(DIGITAL,8);
                        --total;JudgeIsWin();
                    }
                    //cout<<"My surrounding have 8 mines."<<endl;
                    break;
                default:
                    break;
                }
            }
        }
    }
}
bool MainWindow::JudgeIsWin(){
    if(0==remainminenum && Field->getmine()==total){
     QMessageBox::information(this,"Result","You win! New game will start...");
        on_actionNew_game_triggered();
        return true;
    }
    return false;
}
void MainWindow::display(){
    int n=Field->getheight();
    int m=Field->getwide();
    static double cw = IsScale ? sw*this->width()/_scene->width()*factor_Scale : sw;
    static double ch = IsScale ?  sh*this->width()/_scene->width()*factor_Scale : sh;
        double cx;
        double cy;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cx=(IsScale?270:719)+i*cw;
            cy=(IsScale?160:365)+j*ch;
            QGraphicsItem *item =_view->itemAt(cx, cy-35);
            _cItem=dynamic_cast<cellItem*>(item);
            if(_cItem->isvisit||!_cItem)continue;
            switch(Field->_field[i][j]){
            case -1:

                _cItem->setstatus(EXPLORE);

                break;
            case 0:
                _cItem->setstatus(BLANK);
                break;

            case 1:
                _cItem->setstatus(DIGITAL,1);

                break;
            case 2:
                _cItem->setstatus(DIGITAL,2);

                break;
            case 3:
                _cItem->setstatus(DIGITAL,3);

                break;
            case 4:
                _cItem->setstatus(DIGITAL,4);

                break;
            case 5:
                _cItem->setstatus(DIGITAL,5);

                break;
            case 6:
                _cItem->setstatus(DIGITAL,6);

                break;
            case 7:
                _cItem->setstatus(DIGITAL,7);

                break;
            case 8:
                _cItem->setstatus(DIGITAL,8);

                break;
            }
        }
    }
}
void MainWindow::display1(double px,double py,int x,int y){
    Field->initvisit();

    QGraphicsItem *item =_view->itemAt(px, py-35);

    static double cw = IsScale ?  item->boundingRect().width()*this->width()/_scene->width()*factor_Scale : item->boundingRect().width();
    static double ch = IsScale ?  item->boundingRect().height()*this->width()/_scene->width()*factor_Scale : item->boundingRect().height();
    sh=ch,sw=cw;
    const int dir[8][2]={{0, 1}, {1, 0}, {0, -1}, {-1, 0},//下,右,上,左
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}//右下,右上,左上,左下
    };//八个方向可以扩展

    queue<pair<Point_Px,int>> que;//保存鼠标坐标和数据矩阵坐标
    que.push(pair<Point_Px,int>({px,py},x*Field->getheight()+y));
    Field->_visited[x][y]=1;
    while(!que.empty()){
            pair<Point_Px,int> fr=que.front();
            que.pop();
            px=fr.first.px;
            py=fr.first.py;
            x=fr.second/Field->getheight();
            y=fr.second%Field->getheight();

            for(int i=0;i<8;++i){//8个方向扩展
                double npx=px+cw*dir[i][0];
                double npy=py+ch*dir[i][1];
                int nx=x+dir[i][0];
                int ny=y+dir[i][1];
                //超出边界判断
                //qDebug()<<npx<<npy<<nx<<ny;
                if(nx<0 || nx>=Field->getwide() || ny<0 || ny>=Field->getheight()
                    || Field->_visited[nx][ny]){
                    //qDebug()<<"miaomiao-continue";
                    continue;
                }

                item =_view->itemAt(npx, npy-35);
                _cItem=dynamic_cast<cellItem*>(item);

                //显示图片了的不在加入


                //如果数字为0，表示周围没有雷，则继续加入队列进行下去


                    que.push(pair<Point_Px,int>({npx,npy},nx*Field->getheight()+ny));
                    Field->_visited[nx][ny]=1;
                    if(_cItem->isvisit)
                    {continue;}


                    switch (Field->_field[nx][ny]) {
                    case -1:

                        _cItem->setstatus(EXPLORE);

                        break;
                    case 0:
                        _cItem->setstatus(BLANK);
                        break;

                    case 1:
                        _cItem->setstatus(DIGITAL,1);

                        break;
                    case 2:
                        _cItem->setstatus(DIGITAL,2);

                        break;
                    case 3:
                        _cItem->setstatus(DIGITAL,3);

                        break;
                    case 4:
                        _cItem->setstatus(DIGITAL,4);

                        break;
                    case 5:
                        _cItem->setstatus(DIGITAL,5);

                        break;
                    case 6:
                        _cItem->setstatus(DIGITAL,6);

                        break;
                    case 7:
                        _cItem->setstatus(DIGITAL,7);

                        break;
                    case 8:
                        _cItem->setstatus(DIGITAL,8);

                        break;
                    }

            }
        }

}
