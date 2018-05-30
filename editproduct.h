#ifndef EDITPRODUCT_H
#define EDITPRODUCT_H

#include <QDialog>

namespace Ui {
class EditProduct;
}

class EditProduct : public QDialog
{
    Q_OBJECT

public:
    explicit EditProduct(QWidget *parent = 0);
    ~EditProduct();
    void setDataProduct(const int &row_num_product);
    int product_id;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditProduct *ui;
};

#endif // EDITPRODUCT_H
