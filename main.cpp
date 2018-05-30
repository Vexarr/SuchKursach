#include "shopinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShopInfo w;
    w.show();

    return a.exec();
}
