#include "addrec.h"
#include "ui_addrec.h"

AddRec::AddRec(Database* data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addRec)
{
    ui->setupUi(this);
    _data = data;

     QPixmap addRec("C:/Users/Jarvis/Desktop/oop/Term 4/Lab 4/database/images/036-add.png");
    this->setWindowIcon((QIcon(addRec)));

    connect(ui->pushButton_addRecord, &QPushButton::clicked, this, &AddRec::addRecord);
    connect(ui->pushButton_Quit, &QPushButton::clicked, this, &AddRec::close);
}

AddRec::~AddRec()
{
    delete ui;
}


void AddRec::addRecord(){

    try {
    this->_data->appendData(
                ui->lineEdit_Name->text(),
                ui->lineEdit_SecondName->text(),
                ui->lineEdit_Patronymic->text(),
                ui->lineEdit_Number->text()
                );
    } catch (Database::exception_database e) {;}

    ui->lineEdit_Name->setText("");
    ui->lineEdit_SecondName->setText("");
    ui->lineEdit_Patronymic->setText("");
    ui->lineEdit_Number->setText("");


}
