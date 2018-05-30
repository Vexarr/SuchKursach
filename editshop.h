#ifndef EDITSHOP_H
#define EDITSHOP_H

#include <QDialog>

namespace Ui {
class EditShop;
}

class EditShop : public QDialog
{
    Q_OBJECT

public:
    explicit EditShop(QWidget *parent = 0);
    ~EditShop();
    void setData(const int &row_num);
    int shop_id;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditShop *ui;
};

#endif // EDITSHOP_H
