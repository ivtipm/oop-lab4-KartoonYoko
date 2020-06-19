#ifndef ADDREC_H
#define ADDREC_H

#include <QWidget>
#include "database.h"

namespace Ui {
class addRec;
}

class AddRec : public QWidget
{
    Q_OBJECT

public:
    explicit AddRec(Database* data, QWidget *parent = nullptr);
    ~AddRec();
public slots:
    void addRecord();

private:
    Database* _data;
    Ui::addRec *ui;
};

#endif // ADDREC_H
