#ifndef CELLITEM_H
#define CELLITEM_H


#include <QGraphicsPixmapItem>
#include <QPixmap>
enum cellstatus{
    INITSTSTUS,QUESTION,FLAG,DIGITAL,EXPLORE,BLANK
};

class cellItem : public QGraphicsPixmapItem {
public:
    cellItem(int x, int y,
             enum cellstatus status = INITSTSTUS, QGraphicsItem *parent = Q_NULLPTR);
    ~cellItem();
    void setstatus(enum cellstatus status,int digit=-5);
     enum cellstatus getStatus();
    static QPixmap * _initial;
    static QPixmap * _flag;
    static QPixmap * _question;
    static QPixmap * _blank;
    static QPixmap * _explode;
    static QPixmap * _digits[9];
    bool isvisit;
    static int _refCount;
protected:
    int cx,cy;
    cellstatus cell_status;
};

#endif // CELLITEM_H
