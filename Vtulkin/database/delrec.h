#ifndef DELREC_H
#define DELREC_H

#include <QWidget>
#include "database.h"

namespace Ui {
class delRec;
}

class DelRec : public QWidget
{
    Q_OBJECT

public:
    explicit DelRec(Database* data, QWidget *parent = nullptr);
    ~DelRec();

public slots:
    void deleteRecord();

private:
    Database* _data;
    Ui::delRec *ui;
};

#endif // DELREC_H
