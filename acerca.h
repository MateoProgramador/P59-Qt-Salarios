#ifndef ACERCA_H
#define ACERCA_H

#include <QDialog>

namespace Ui {
class acerca;
}

class acerca : public QDialog
{
    Q_OBJECT

public:
    explicit acerca(QWidget *parent = nullptr);
    ~acerca();

private:
    Ui::acerca *ui;
};

#endif // ACERCA_H
