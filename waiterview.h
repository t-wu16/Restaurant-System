#ifndef WAITERVIEW_H
#define WAITERVIEW_H

#include "headfile.h"
#include "waiter.h"
#include "tableview.h"
namespace Ui {
class WaiterView;
}
class WaiterView : public QDialog
{
    Q_OBJECT

public:
    explicit WaiterView(QWidget *parent = 0, Waiter *waiter = NULL, Table *table1 = NULL);
    ~WaiterView();

private slots:
    void service_begin_clicked();
    void get_table_clicked();
    void btn_clicked(int i);

private:
    Ui::WaiterView *ui;
    QButtonGroup *my_button;
    Waiter *waiter;
    Table *table[3];
    int table_number;

};

#endif // WAITERVIEW_H
