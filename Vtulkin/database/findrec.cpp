#include "findrec.h"
#include "ui_findrec.h"

FindRec::FindRec(Database* data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findRec)
{
    ui->setupUi(this);
    _data = data;
    buf = nullptr;


    connect(ui->pushButton_findRecord, &QPushButton::clicked, this, &FindRec::findRecord);
    connect(ui->pushButton_change, &QPushButton::clicked, this, &FindRec::changeRecord);
    connect(ui->pushButton_Quit, &QPushButton::clicked, this, &FindRec::close);
}

FindRec::~FindRec()
{
    delete ui;
}



void FindRec::findRecord(){
    try {
        buf = _data->find(ui->lineEdit_Name->text(),
                   ui->lineEdit_SecondName->text(),
                   ui->lineEdit_Patronymic->text(),
                   ui->lineEdit_Number->text()
                   );

        QVariant str;
        str = (*buf)[Database::FIRST_COLUMN];
        ui->lineEdit_Name->setText(str.toString());

        str = (*buf)[Database::SECOND_COLUMN];
        ui->lineEdit_SecondName->setText(str.toString());

        str = (*buf)[Database::THIRD_COLUMN];
        ui->lineEdit_Patronymic->setText(str.toString());

        str = (*buf)[Database::FOURTH_COLUMN];
        ui->lineEdit_Number->setText(str.toString());




    } catch (Database::exception_database e) {qDebug() << "exception is catched";}
}


void FindRec::changeRecord(){

    if (buf != nullptr){
        (*buf)[Database::FIRST_COLUMN] = ui->lineEdit_Name->text();
        (*buf)[Database::SECOND_COLUMN] = ui->lineEdit_SecondName->text();
        (*buf)[Database::THIRD_COLUMN] = ui->lineEdit_Patronymic->text();

        int b = ui->lineEdit_Number->text().toInt();
        if (b <= 9999 && b >= 1000 )
            (*buf)[Database::FOURTH_COLUMN] =  ui->lineEdit_Number->text();
        _data->resetModel();
    }
}


