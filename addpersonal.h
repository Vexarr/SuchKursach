#ifndef ADDPERSONAL_H
#define ADDPERSONAL_H

#include <QDialog>

namespace Ui {
class AddPersonal;
}

class AddPersonal : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonal(QWidget *parent = 0);
    ~AddPersonal();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddPersonal *ui;
};

#endif // ADDPERSONAL_H
