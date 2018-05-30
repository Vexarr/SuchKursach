#ifndef EDITBUY_H
#define EDITBUY_H

#include <QDialog>

namespace Ui {
class EditBuy;
}

class EditBuy : public QDialog
{
    Q_OBJECT

public:
    explicit EditBuy(QWidget *parent = 0);
    ~EditBuy();
    void setDataBuy(const int &row_num_buy);
    int buy_id;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditBuy *ui;
};

#endif // EDITBUY_H
