#include "delrec.h"
#include "ui_delrec.h"

DelRec::DelRec(Database* data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delRec)
{
    ui->setupUi(this);
    _data = data;

    QPixmap delRec("C:/Users/Jarvis/Desktop/oop/Term 4/Lab 4/database/images/037-delete.png");
    this->setWindowIcon((QIcon(delRec)));

    connect(ui->pushButton_delete, &QPushButton::clicked, this, &DelRec::deleteRecord);
    connect(ui->pushButton_Quit, &QPushButton::clicked, this, &DelRec::close);

}

DelRec::~DelRec()
{
    delete ui;
}



void DelRec::deleteRecord(){

    int count;
    count = ui->spinBox_to->value() - ui->spinBox_since->value() + 1;
    if (count >= 0)
        _data->removeRows(ui->spinBox_since->value(), count);
}
