#ifndef COOKVIEW_H
#define COOKVIEW_H

#include <QDialog>
#include "headfile.h"
#include "cook.h"

namespace Ui {
class CookView;
}

class CookView : public QDialog
{
    Q_OBJECT

public:
    explicit CookView(QWidget *parent = 0, Cook *cook = NULL);
    ~CookView();

private:
    Ui::CookView *ui;
    Cook *cook;         //厨师对象

};

#endif // COOKVIEW_H
