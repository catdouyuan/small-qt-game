#include "cellitem.h"

int cellItem::_refCount=0;
QPixmap * cellItem::_initial    =   nullptr;
QPixmap * cellItem::_flag       =   nullptr;
QPixmap * cellItem::_question   =   nullptr;
QPixmap * cellItem::_blank      =   nullptr;
QPixmap * cellItem::_explode    =   nullptr;
QPixmap * cellItem::_digits[9]  =   {nullptr};

cellItem::cellItem(int x, int y,
                   enum cellstatus status , QGraphicsItem *parent ):
    QGraphicsPixmapItem(parent) {
    cx=x;
    cy=y;
    isvisit=0;
    cell_status =status;
    ++_refCount;//创建第一个cellItem时加载所有图片

    if(_refCount == 1) {//引用计数，保证只new一次
        _initial    =   new QPixmap("://images/images30/initial.png");
        _flag       =   new QPixmap("://images/images30/flag.png");
        _question   =   new QPixmap("://images/images30/question.png");
        _blank      =   new QPixmap("://images/images30/blank.png");
        _explode    =   new QPixmap("://images/images30/explode.png");

        QString prefix = "://images/images30/";
        QString num;
        QString suffix = ".png";

        for(int i=1;i<9;++i){
            QString fileName;
            fileName+=prefix;
            fileName+=num.setNum(i);
            fileName+=suffix;
            _digits[i] = new QPixmap(fileName);
        }
    }
    setPixmap(*_initial);
}
cellItem::~cellItem(){
    //释放所有cellItem后，释放图片
    if(--_refCount == 0){
        delete _initial   ;
        delete _flag      ;
        delete _question  ;
        delete _blank     ;
        delete _explode   ;
        for(int i=0;i<9;++i){
            delete _digits[i];
        }
    }
}
enum cellstatus cellItem::getStatus(){
    return cell_status;
}
void cellItem::setstatus(enum cellstatus status,int digit){
    isvisit=1;
    cell_status=status;
    switch(cell_status){
    case  INITSTSTUS:
        setPixmap(*_initial);
        break;
    case FLAG:
        setPixmap(*_flag);
        break;
    case QUESTION:
        setPixmap(*_question);
        break;
    case EXPLORE:
        setPixmap(*_explode);
        break;
    case DIGITAL:
        setPixmap(*_digits[digit]);
        break;
    case BLANK:
        setPixmap(*_blank);
        break;
    default:
        break;
    }
}
