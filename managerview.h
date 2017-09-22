#ifndef MANAGERVIEW_H
#define MANAGERVIEW_H

#include <headfile.h>

namespace Ui {
class ManagerView;
}

class ManagerView : public QDialog
{
    Q_OBJECT

public:
    explicit ManagerView(QWidget *parent = 0);
    ~ManagerView();

private slots:
    void on_quit_btn_clicked();

private:
    Ui::ManagerView *ui;
};

#endif // MANAGERVIEW_H
