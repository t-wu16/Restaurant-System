#ifndef FORGOT_H
#define FORGOT_H

#include <headfile.h>

namespace Ui {
class Forgot;
}

class Forgot : public QDialog
{
    Q_OBJECT

public:
    explicit Forgot(QWidget *parent = 0);
    ~Forgot();

private slots:
    void on_get_btn_clicked();

    void on_get_btn_2_clicked();

    void on_get_btn_3_clicked();

private:
    Ui::Forgot *ui;
    QString password;
};

#endif // FORGOT_H
