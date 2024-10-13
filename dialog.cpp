#include "dialog.h"
#include "ui_dialog.h"

#include <QIntValidator>
Dialog::Dialog(int ch,int cw,int num,QWidget *parent)
    : QDialog(parent),_height(ch),_wide(cw),_minenum(num),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QIntValidator * vaildW = new QIntValidator(1, 30, this);//宽度限制
    QIntValidator * vaildH = new QIntValidator(1, 19, this);//高度限制
    QIntValidator * vaildM = new QIntValidator(0, 570, this);//雷数初步限制(后面还有个数检查)
    ui->lineheight->setValidator(vaildH);
    ui->linewide->setValidator(vaildW);
    ui->linenumber->setValidator(vaildM);


}



void Dialog::accept(){

    _wide=ui->linewide->text().toInt();
    _height=ui->lineheight->text().toInt();
    _minenum=ui->linenumber->text().toInt();

    QDialog::accept();//自己的实现以后，再显示调用父类的accept槽
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    accept();
}


void Dialog::on_pushButton_2_clicked()
{
    close();
}

