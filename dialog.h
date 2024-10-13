#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int ch,int cw,int num,QWidget *parent = nullptr);
    ~Dialog();
    int _height;
    int _wide;
    int _minenum;
private slots:

    void accept();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
