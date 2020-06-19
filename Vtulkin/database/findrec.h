#ifndef FINDREC_H
#define FINDREC_H

#include <QWidget>
#include "database.h"

namespace Ui {
class findRec;
}

class FindRec : public QWidget
{
    Q_OBJECT

public:
    explicit FindRec(Database* data, QWidget *parent = nullptr);
    ~FindRec();

public slots:

    void findRecord();
    void changeRecord();


private:
    Database* _data;
    Database::typeOfRow* buf;
    Ui::findRec *ui;
};

#endif // FINDREC_H
