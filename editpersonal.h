#ifndef EDITPERSONAL_H
#define EDITPERSONAL_H

#include <QDialog>

namespace Ui {
class EditPersonal;
}

class EditPersonal : public QDialog
{
    Q_OBJECT

public:
    explicit EditPersonal(QWidget *parent = 0);
    ~EditPersonal();
    void setDataPerson(const int &row_num_person);
    int person_id;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditPersonal *ui;
};

#endif // EDITPERSONAL_H
