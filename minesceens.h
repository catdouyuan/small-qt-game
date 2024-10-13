#ifndef MINESCEENS_H
#define MINESCEENS_H
#include <QGraphicsScene>
#include "cellItem.h"
#include <vector>
using namespace std;


typedef vector<cellItem*> ItemColumn;
typedef vector<ItemColumn> ItemMatrix;

class mineSweepScene : public QGraphicsScene
{
public:
    mineSweepScene(QObject *parent = Q_NULLPTR);
    ~mineSweepScene();

    void initItems();
    void clearItems();
    void scenedisplay();
    //prot  ected:
    ItemMatrix _items;

};

#endif // MINESCEENS_H
