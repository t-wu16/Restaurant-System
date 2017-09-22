#include "managerview.h"
#include "ui_managerview.h"

extern QList<Waiter> waiterList;
extern QList<Customer> customerList;
extern QList<Bill> billList;

ManagerView::ManagerView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerView)
{
    ui->setupUi(this);

    //服务员信息
    ui->waiter_widget->setColumnCount(4);
    ui->waiter_widget->setRowCount(15);
    ui->waiter_widget->setHorizontalHeaderLabels(QStringList()<<"帐号"<<"姓名"<<"评价次数"<<"平均评分");
    ui->waiter_widget->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中行的方式
    ui->waiter_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->waiter_widget->verticalHeader()->setVisible(false);                     //隐藏列表头
    this->setStyleSheet("QDialog{border-image:url(:/img/background2.jpg)}");

    for(int i=0;i<4;i++)
    {
        ui->waiter_widget->setColumnWidth(i,106);
    }
    for(int i=0;i<waiterList.length();i++)
    {
        string id = waiterList[i].getId().c_str();
        string name = waiterList[i].getName().c_str();
        int times = waiterList[i].getCommentTimes();
        if(times!=0)
        {
            int score = waiterList[i].getCommentScore()/waiterList[i].getCommentTimes();
            QString str_score = QString("%1").arg(score);
            QTableWidgetItem *item3 = new QTableWidgetItem(str_score);
            ui->waiter_widget->setItem(i,3,item3);
        }
        QString str_times = QString("%1").arg(times);
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(id));
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(name));
        QTableWidgetItem *item2 = new QTableWidgetItem(str_times);
        ui->waiter_widget->setItem(i,0,item0);
        ui->waiter_widget->setItem(i,1,item1);
        ui->waiter_widget->setItem(i,2,item2);
    }

    //厨师信息
    ui->cook_widget->setColumnCount(4);
    ui->cook_widget->setRowCount(15);
    ui->cook_widget->setHorizontalHeaderLabels(QStringList()<<"帐号"<<"姓名"<<"完成菜品"<<"单次数量");
    ui->cook_widget->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中行的方式
    ui->cook_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->cook_widget->verticalHeader()->setVisible(false);                     //隐藏列表头
    for(int i=0;i<4;i++)
    {
        ui->cook_widget->setColumnWidth(i,106);
    }
    for(int i=0;i<billList.length();i++)
    {
        string id = billList[i].getCookId().c_str();
        string name = billList[i].getCookName().c_str();
        string dish_name = billList[i].getDishName().c_str();
        int num = billList[i].getNum();
        QString str_num = QString("%1").arg(num);
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(id));
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(name));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(dish_name));
        QTableWidgetItem *item3  =new QTableWidgetItem(str_num);
        ui->cook_widget->setItem(i,0,item0);
        ui->cook_widget->setItem(i,1,item1);
        ui->cook_widget->setItem(i,2,item2);
        ui->cook_widget->setItem(i,3,item3);
    }
}

ManagerView::~ManagerView()
{
    delete ui;
}

//退出按钮
void ManagerView::on_quit_btn_clicked()
{
    this->hide();
}
