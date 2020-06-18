#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    timer = new QTimer();
    // saved progress each 5 minutes(300 000 msec)
    timer->setInterval(300000);
    connect(timer, &QTimer::timeout, this, &MainWindow::saveData);
    timer->start();

    ui->tableView->setModel(database = new Database);
    addToolBar(Qt::TopToolBarArea, createToolBar());

    QPixmap mainIcon("C:/Users/Jarvis/Desktop/oop/Term 4/Lab 4/database/images/029-coding.png");
    this->setWindowIcon((QIcon(mainIcon)));


    // creating menu
    QPixmap addRec(":/images/036-add.png");
    QPixmap deleteRec(":/images/037-delete.png");
    QPixmap findRec(":/images/009-search.png");
    QPixmap sortData(":/images/010-exchange.png");
    QPixmap saveData(":/images/019-save.png");
    QPixmap downloadData(":/images/001-download.png");

    ui->menu->addAction(QIcon(saveData), "Сохранить", this, SLOT(saveData()), tr("Ctrl+S"));
    ui->menu->addAction(QIcon(downloadData), "Загрузить", this, SLOT(downloadData()), tr("Ctrl+D"));
    ui->menu->addSeparator();
    ui->menu->addAction(QIcon(addRec), "Добавить запись", this, SLOT(addRecord()), tr("Ctrl+A"));
    ui->menu->addAction(QIcon(deleteRec), "Удалить запись", this, SLOT(deleteRecords()), tr("Ctrl+R"));
    ui->menu->addAction(QIcon(findRec), "Поиск", this, SLOT(findRec()), tr("Ctrl+F"));
    ui->menu->addAction(QIcon(sortData), "Сортировка", this, SLOT(sortData()), tr("Ctrl+O"));

    ui->menu_2->addAction("Помощь", this, SLOT(help()));
    ui->menu_2->addSeparator();
    ui->menu_2->addAction("О разработчике", this, SLOT(aboutCreator()));

}

QToolBar* MainWindow::createToolBar()
{
    QToolBar* ptb = new QToolBar("Linker ToolBar");

    ptb->setIconSize(QSize(50, 50));
    ptb->setMovable(false);

    QPixmap addRec(":/images/036-add.png");
    //QPixmap addRec("C:/Users/Jarvis/Desktop/oop/Term 4/Lab 4/database/images/036-add.png");
    QPixmap deleteRec(":/images/037-delete.png");
    QPixmap findRec(":/images/009-search.png");
    QPixmap sortData(":/images/010-exchange.png");
    QPixmap saveData(":/images/019-save.png");
    QPixmap downloadData(":/images/001-download.png");


    ptb->addAction(QIcon(saveData), "Сохранить", this, SLOT(saveData()));
    ptb->addAction(QIcon(downloadData), "Загрузить", this, SLOT(downloadData()));
    ptb->addSeparator();
    ptb->addAction(QIcon(addRec), "Добавить запись", this, SLOT(addRecord()));
    ptb->addAction(QIcon(deleteRec), "Удалить запись", this, SLOT(deleteRecords()));
    ptb->addAction(QIcon(findRec), "Поиск", this, SLOT(findRec()));
    ptb->addAction(QIcon(sortData), "Сортировка", this, SLOT(sortData()));
    ptb->addSeparator();

    return ptb;
}


void MainWindow::aboutCreator(){

    AboutCreator* window = new AboutCreator();
    window->show();
}
void MainWindow::help(){

    Help* window = new Help();
    window->show();
}

void MainWindow::saveData(){

    if (!database->empty())
        database->saveToFile("");
}
void MainWindow::downloadData(){

    try {
        database->readFromFile("");
    } catch (Database::exception_database e) {;}
}

void MainWindow::addRecord(){

    AddRec* window = new AddRec(this->database);
    window->show();

}
void MainWindow::deleteRecords(){

    DelRec* window = new DelRec(database);
    window->show();
}
void MainWindow::sortData(){

    //switch(ui->spinBox->value()){
    //    case 0: database->sort(Database::FIRST_COLUMN, Qt::SortOrder::AscendingOrder); break;
    //    case 1: database->sort(Database::SECOND_COLUMN, Qt::SortOrder::AscendingOrder); break;
    //    case 2: database->sort(Database::THIRD_COLUMN, Qt::SortOrder::AscendingOrder); break;
    //    case 3: database->sort(Database::FOURTH_COLUMN, Qt::SortOrder::AscendingOrder); break;
    //}
    try
    {
        database->sort(Database::FIRST_COLUMN, Qt::SortOrder::AscendingOrder);
    }
    catch(Database::exception_database e){;}
}
void MainWindow::findRec(){

    FindRec* window = new FindRec(database);
    window->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}


