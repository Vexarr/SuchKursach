#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = 0);
    ~AddProduct();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddProduct *ui;
};

#endif // ADDPRODUCT_H
