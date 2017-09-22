#include "cookview.h"
#include "ui_cookview.h"
extern QVector<Table> tableVector;
extern QList<OrderCuisine> orderList;

CookView::CookView(QWidget *parent, Cook *cook) :
    QDialog(parent),cook(cook),
    ui(new Ui::CookView)
{
    i=0;
    all_mission_row = 0;
    my_mission_row = 0;
    all_mission_row_now = -1;
    my_mission_row_now = -1;
    ui->setupUi(this);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);
    this->setWindowTitle("厨师任务系统");
    this->setStyleSheet("QDialog{border-image:url(:/img/background2.jpg)}");

    //绘制全部任务列表
    ui->all_mission_widget->setColumnCount(4);
    ui->all_mission_widget->setRowCount(10);
    ui->all_mission_widget->setHorizontalHeaderLabels(QStringList()<<"菜名"<<"数量"<<"备注"<<"桌号");
    ui->all_mission_widget->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
    ui->all_mission_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->all_mission_widget->verticalHeader()->setVisible(false);                     //隐藏列表头
    ui->all_mission_widget->setShowGrid(false);
    for(int i=0;i<4;i++)
    {
        ui->all_mission_widget->setColumnWidth(i,109);
    }

    QList<CookMission>::iterator iter;
    for(iter=cook->getAllMission().begin();iter!=cook->getAllMission().end();iter++)
    {        
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(iter->getDishName()));
        QTableWidgetItem *item1 = new QTableWidgetItem(QString("%1").arg(iter->getNum()));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(iter->getRemark()));
        QTableWidgetItem *item3 = new QTableWidgetItem(QString("%1").arg(iter->getTableNumber()));
        ui->all_mission_widget->setItem(all_mission_row,0,item0);
        ui->all_mission_widget->setItem(all_mission_row,1,item1);
        ui->all_mission_widget->setItem(all_mission_row,2,item2);
        ui->all_mission_widget->setItem(all_mission_row,3,item3);
        all_mission_row++;
    }


    //绘制我的任务列表
    ui->my_mission_widget->setColumnCount(5);
    ui->my_mission_widget->setRowCount(10);
    ui->my_mission_widget->setHorizontalHeaderLabels(QStringList()<<"菜名"<<"数量"<<"备注"<<"桌号"<<"进度");
    ui->my_mission_widget->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
    ui->my_mission_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->my_mission_widget->verticalHeader()->setVisible(false);                     //隐藏列表头
    ui->my_mission_widget->setShowGrid(false);
    for(int i=0;i<5;i++)
    {
        ui->my_mission_widget->setColumnWidth(i,60);
    }

    //connect
    connect(ui->all_mission_widget,SIGNAL(clicked(QModelIndex)),this,SLOT(get_all_mission_list()));
    connect(ui->my_mission_widget,SIGNAL(clicked(QModelIndex)),this,SLOT(get_my_mission_list()));
    connect(ui->get_mission_btn,SIGNAL(clicked()),this,SLOT(get_mission_btn_clicked()));
    connect(ui->begin_mission_btn,SIGNAL(clicked()),this,SLOT(begin_mission_btn_clicked()));
    connect(ui->finish_mission_btm,SIGNAL(clicked()),this,SLOT(finish_mission_btn_clicked()));
    connect(ui->quit_btn,SIGNAL(clicked()),this,SLOT(quit_btn_clicked()));

}

CookView::~CookView()
{
    delete ui;
}

/*槽函数*/

//获取全部任务内容
void CookView::get_all_mission_list()
{
    all_mission_row_now = ui->all_mission_widget->currentRow(); //点击的行号
    if(all_mission_row_now < all_mission_row && all_mission_row_now!=-1)
    {
        dish_name = ui->all_mission_widget->item(all_mission_row_now,0)->text();
        num = ui->all_mission_widget->item(all_mission_row_now,1)->text().toInt();
        remark = ui->all_mission_widget->item(all_mission_row_now,2)->text();
        table_number = ui->all_mission_widget->item(all_mission_row_now,3)->text().toInt();
    }
}

//认领菜品
void CookView::get_mission_btn_clicked()
{
    if(all_mission_row_now < all_mission_row && all_mission_row_now != -1)
    {
        //添加到我的任务列表
        QTableWidgetItem *item0 = new QTableWidgetItem(dish_name);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString("%1").arg(num));
        QTableWidgetItem *item2 = new QTableWidgetItem(remark);
        QTableWidgetItem *item3 = new QTableWidgetItem(QString("%1").arg(table_number));
        QTableWidgetItem *item4 = new QTableWidgetItem("未完成");
        ui->my_mission_widget->setItem(my_mission_row, 0, item0);
        ui->my_mission_widget->setItem(my_mission_row, 1, item1);
        ui->my_mission_widget->setItem(my_mission_row, 2, item2);
        ui->my_mission_widget->setItem(my_mission_row, 3, item3);
        ui->my_mission_widget->setItem(my_mission_row, 4, item4);
        my_mission_row++;

        //后台
        CookMission mission(dish_name.toStdString(),num,remark.toStdString(),table_number);
        cook->addMission(mission);

        //更新所有任务列表,重新绘制表
        cook->deleteMission(mission);
        all_mission_row = 0;
        ui->all_mission_widget->clear();
        ui->all_mission_widget->setColumnCount(4);
        ui->all_mission_widget->setRowCount(10);
        ui->all_mission_widget->setHorizontalHeaderLabels(QStringList()<<"菜名"<<"数量"<<"备注"<<"桌号");
        ui->all_mission_widget->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
        ui->all_mission_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
        ui->all_mission_widget->verticalHeader()->setVisible(false);                     //隐藏列表头
        ui->all_mission_widget->setShowGrid(false);
        QList<CookMission>::iterator iter;
        for(iter=cook->getAllMission().begin();iter!=cook->getAllMission().end();iter++)
        {
            QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(iter->getDishName()));
            QTableWidgetItem *item1 = new QTableWidgetItem(QString("%1").arg(iter->getNum()));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(iter->getRemark()));
            QTableWidgetItem *item3 = new QTableWidgetItem(QString("%1").arg(iter->getTableNumber()));
            ui->all_mission_widget->setItem(all_mission_row,0,item0);
            ui->all_mission_widget->setItem(all_mission_row,1,item1);
            ui->all_mission_widget->setItem(all_mission_row,2,item2);
            ui->all_mission_widget->setItem(all_mission_row,3,item3);
            all_mission_row++;
        }

    }
}

//获取我的任务
void CookView::get_my_mission_list()
{
    my_mission_row_now = ui->my_mission_widget->currentRow();
    if(my_mission_row_now < my_mission_row && my_mission_row_now!=-1)
    {
        my_dish_name = ui->my_mission_widget->item(my_mission_row_now,0)->text();
        my_num = ui->my_mission_widget->item(my_mission_row_now,1)->text().toInt();
        my_remark = ui->my_mission_widget->item(my_mission_row_now,2)->text();
        my_table_number = ui->my_mission_widget->item(my_mission_row_now,3)->text().toInt();
    }
}

//开始做菜
void CookView::begin_mission_btn_clicked()
{
    ui->current_mission->setText(my_dish_name);
}

//完成菜品
void CookView::finish_mission_btn_clicked()
{
    QTableWidgetItem *item = new QTableWidgetItem("完成");
    ui->current_mission->clear();
    ui->my_mission_widget->setItem(i,4,item);
    i++;

    for(int i=0;i<orderList.length();i++)
    {
        if(my_dish_name == orderList[i].getName().c_str()
           && my_table_number == orderList[i].getTableNumber()+1)
        {
            orderList[i].setState("完成");
            break;
        }
    }
}

//退出
void CookView::quit_btn_clicked()
{
    this->hide();
    MainData m;
    m.dataOut2();
}
