#ifndef ADDBUY_H
#define ADDBUY_H

#include <QDialog>

namespace Ui {
class AddBuy;
}

class AddBuy : public QDialog
{
    Q_OBJECT

public:
    explicit AddBuy(QWidget *parent = 0);
    ~AddBuy();

private slots:
    void on_DialogButtonBox_accepted();

    void on_AddInBuy_clicked();

    void on_DialogButtonBox_rejected();

private:
    Ui::AddBuy *ui;
};

#endif // ADDBUY_H
