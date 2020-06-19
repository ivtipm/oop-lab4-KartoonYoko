#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QToolBar>
#include <QIcon>
#include <QDialog>
#include <QTimer>

#include "database.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "addrec.h"
#include "delrec.h"
#include "findrec.h"
#include "aboutcreator.h"
#include "help.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* timer;

    QToolBar* createToolBar();

private slots:

    void addRecord();
    void deleteRecords();
    void sortData();
    void findRec();
    void saveData();
    void downloadData();

    void aboutCreator();
    void help();

private:
    Ui::MainWindow *ui;
    Database* database;

public:




};
#endif // MAINWINDOW_H
