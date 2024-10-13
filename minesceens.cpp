#include "minesceens.h"
#include "fielddata.h"
#include <QGraphicsPixmapItem>
mineSweepScene::mineSweepScene(QObject *parent):
    QGraphicsScene(parent)
{
    initItems();
}

mineSweepScene::~mineSweepScene(){
    clearItems();
}
void mineSweepScene::initItems(){
     int w = Field->getwide();
    int h=Field->getheight();
     for(int x=0;x<w;++x){
         _items.push_back(ItemColumn());
         for(int y=0;y<h;++y){
             _items[x].push_back(new cellItem(x,y));
             static int cw = _items[0][0]->boundingRect().width();//图片的大小
             static int ch = _items[0][0]->boundingRect().height();

             _items[x][y]->setPos(x*cw,y*ch);
             addItem(_items[x][y]);
         }
     }
}
void mineSweepScene::clearItems(){
    int w = Field->getwide();
    int h = Field->getheight();

    for(int x=0;x<w;++x){
        for(int y=0;y<h;++y){
            delete _items[x][y];
            _items[x][y]=nullptr;
        }
    }
    _items.clear();
}
void mineSweepScene::scenedisplay(){
    int w = Field->getwide();
    int h=Field->getheight();
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
           cellItem *_cItem=_items[i][j];
            if(_cItem->isvisit)
            {continue;}


            switch (Field->_field[i][j]) {
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
