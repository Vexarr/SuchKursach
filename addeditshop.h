#ifndef ADDEDITSHOP_H
#define ADDEDITSHOP_H

#include <QDialog>
#include <shopinfo.h>

namespace Ui {
class AddEditShop;
}

class AddEditShop : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditShop(QWidget *parent = 0);
    ~AddEditShop();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddEditShop *ui;
    int iShopId;
};

#endif // ADDEDITSHOP_H
