#ifndef FIELDDATA_H
#define FIELDDATA_H
#include <vector>
using namespace std;
typedef vector<int> CellColumn;
typedef vector<CellColumn> CellMatrix;
#define Field (fielddata::getInstance())//得到指针
class fielddata
{
public:
    fielddata();//单例模式
    ~fielddata();
     static fielddata* getInstance();
    int getwide(){return _wide;}
    int getheight(){return _height;}
    int getmine(){return _minenum;}
    void initcell();
    void delaycell();
    void reset();
    void updateSurrounding(int ,int ,int,int);
    void customize(int ch,int cw,int num);
    void initvisit();
    CellMatrix _field;
    CellMatrix _visited;
private:
 static fielddata * _fuck;

    int _wide,_height,_minenum;
private:

};

#endif // FIELDDATA_H
