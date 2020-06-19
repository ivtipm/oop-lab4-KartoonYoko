#include "aboutcreator.h"
#include "ui_aboutcreator.h"

AboutCreator::AboutCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutCreator)
{
    ui->setupUi(this);
}

AboutCreator::~AboutCreator()
{
    delete ui;
}
