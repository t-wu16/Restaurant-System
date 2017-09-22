#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "headfile.h"

namespace Ui {
class Administrator;
}

class Administrator : public QDialog
{
    Q_OBJECT

public:
    explicit Administrator(QWidget *parent = 0);
    ~Administrator();
    void hideAll();
    void showMenu();
    void showPeople();

private slots:

    void on_menu_btn_clicked();

    void on_commit_btn_clicked();

    void on_revert_btn_clicked();

    void on_delete_btn_clicked();

    void on_select_btn_clicked();

    void on_showall_btn_clicked();

    void on_add_btn_clicked();

    void on_confirm_btn_clicked();

    void on_cancle_btn_clicked();

    void on_people_btn_clicked();

    void on_confirm_btn_2_clicked();

    void on_cancle_btn_2_clicked();

    void on_add_btn_2_clicked();

    void on_back_clicked();

    void on_change_btn_clicked();

    void on_showall_btn_2_clicked();

    void on_delete_btn_2_clicked();

    void on_select_btn_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Administrator *ui;
    QSqlTableModel *model;
    QSqlTableModel *people_model;
};

#endif // ADMINISTRATOR_H
