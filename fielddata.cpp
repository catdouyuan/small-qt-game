#include "fielddata.h"
#include <stdlib.h>
#include <ctime>
fielddata *fielddata::_fuck=nullptr;
fielddata::fielddata():_wide(10),_height(10),_minenum(10) {

    reset();
}
void fielddata::initcell(){
    for(int i=0;i<_wide;i++){
         _visited.push_back(CellColumn(_height));
         _field.push_back(CellColumn(_height));
        for(int j=0;j<_height;j++){
            _visited[i][j]=0;
            _field[i][j]=0;
        }
    }

}
void fielddata::initvisit(){
    for(int i=0;i<_wide;i++){
        _visited.push_back(CellColumn(_height));

        for(int j=0;j<_height;j++){
            _visited[i][j]=0;

        }
    }
}
void fielddata::reset(){
    initcell();
    initvisit();
    srand(time(nullptr));
    delaycell();
}
fielddata::~fielddata(){}
void fielddata::delaycell(){
    int temp=_minenum;
    while(temp){
        int cx=rand()%_height;
        int cy=rand()%_wide;
        if(_visited[cx][cy])continue;
        _visited[cx][cy]=1;
        _field[cx][cy]=-1;
        updateSurrounding(cx - 1, cy - 1,cx,cy); //左上
        updateSurrounding(cx, cy - 1,cx,cy); //上
        updateSurrounding(cx + 1, cy - 1,cx,cy); //右上
        updateSurrounding(cx - 1, cy,cx,cy); //左
        updateSurrounding(cx + 1, cy,cx,cy); //右
        updateSurrounding(cx - 1, cy + 1,cx,cy); //左下
        updateSurrounding(cx, cy + 1,cx,cy); //下
        updateSurrounding(cx + 1, cy + 1,cx,cy); //右下
        temp--;
    }
    for(int x=0;x<_wide;x++){
        for(int y=0;y<_height;y++){

        }
    }
}
void fielddata::updateSurrounding(int x,int y,int a,int b){
    if(x >= 0 && x < _wide && y >= 0 && y < _height) {
        if(_field[x][y] != -1) {
            ++_field[x][y];
        }
    }

}
void fielddata::customize(int ch,int cw,int num){
    _height=ch;
    _wide=cw;
    _minenum=num;
}

fielddata* fielddata::getInstance(){
    if(!_fuck)_fuck=new fielddata;
    return _fuck;
}
