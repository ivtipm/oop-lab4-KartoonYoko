#ifndef ABOUTCREATOR_H
#define ABOUTCREATOR_H

#include <QWidget>

namespace Ui {
class aboutCreator;
}

class AboutCreator : public QWidget
{
    Q_OBJECT

public:
    explicit AboutCreator(QWidget *parent = nullptr);
    ~AboutCreator();

private:
    Ui::aboutCreator *ui;
};

#endif // ABOUTCREATOR_H
