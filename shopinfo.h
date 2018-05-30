#ifndef SHOPINFO_H
#define SHOPINFO_H

#include <QMainWindow>

namespace Ui {
class ShopInfo;
}

class ShopInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShopInfo(QWidget *parent = 0);
    ~ShopInfo();

private slots:
    void on_actionShop_triggered();
    void on_actionProducts_triggered();
    void on_actionPersons_triggered();
    void on_actionBuy_triggered();

    // Страница Магазин
    void on_AddShop_clicked();
    void on_EditShop_clicked();
    void on_RemoveShop_clicked();
    void on_UpdateShop_clicked();

    // Страница Товаров
    void on_AddProduct_clicked();
    void on_EditProduct_clicked();
    void on_RemoveProduct_clicked();
    void on_UpdateProduct_clicked();

    // Страница Персонала
    void on_AddPerson_clicked();
    void on_EditPerson_clicked();
    void on_RemovePerson_clicked();
    void on_UpdatePerson_clicked();

    //Страница Корзины
    void on_AddBuy_clicked();
    void on_EditBuy_clicked();
    void on_RemoveBuy_clicked();
    void on_UpdateBuy_clicked();


private:
    Ui::ShopInfo *ui;
};

#endif // SHOPINFO_H
