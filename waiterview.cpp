#include "waiterview.h"
#include "ui_waiterview.h"

extern QVector<Table> tableVector;
extern QList<OrderCuisine> orderList;
int WaiterView::table_number = 0;
Table* WaiterView::table[3] = {NULL};

WaiterView::WaiterView(QWidget *parent, Waiter *waiter, Table *table1) :
    QDialog(parent), waiter(waiter),
    ui(new Ui::WaiterView)
{
    table[table_number] = table1;
    //界面
    ui->setupUi(this);
    setMinimumSize(1000,700);
    setMaximumSize(1000,700);
    setWindowTitle(tr("服务消息"));
    this->setStyleSheet("QDialog{border-image:url(:/img/background2.jpg)}");
    ui->waiter_id->setText(waiter->getId().c_str());
    if(table_number%3 == 0)
    {
        QString str1 = QString("%1").arg(waiter->getTableNumber(0));
        ui->table_id1->setText(str1);
    }
    if(table_number%3 == 1)
    {
        QString str1 = QString("%1").arg(waiter->getTableNumber(0));
        ui->table_id1->setText(str1);
        QString str2 = QString("%1").arg(waiter->getTableNumber(1));
        ui->table_id2->setText(str2);
    }
    if(table_number%3 == 2)
    {
        QString str1 = QString("%1").arg(waiter->getTableNumber(0));
        ui->table_id1->setText(str1);
        QString str2 = QString("%1").arg(waiter->getTableNumber(1));
        ui->table_id2->setText(str2);
        QString str3 = QString("%1").arg(waiter->getTableNumber(2));
        ui->table_id3->setText(str3);
    }
    my_button = new QButtonGroup(this);
    for(int i=1;i<16;i++)
    {
        QPushButton *btn = new QPushButton(this);
        btn->setStyleSheet("QWidget{border-image:url(:/img/green.png)}");
        my_button->addButton(btn,i);
    }
    for(int i=1;i<6;i++)
    {
        my_button->button(i)->setGeometry(170,210+70*(i-1),41,51);
    }
    for(int i=6;i<11;i++)
    {
        my_button->button(i)->setGeometry(500,210+70*(i-6),41,51);
    }
    for(int i=11;i<16;i++)
    {
        my_button->button(i)->setGeometry(830,210+70*(i-11),41,51);
    }

    //connect
    connect(ui->service_begin,SIGNAL(clicked()),this,SLOT(service_begin_clicked()));
    connect(ui->serve_end,SIGNAL(clicked()),this,SLOT(serve_end_clicked()));
    connect(ui->get_table,SIGNAL(clicked()),this,SLOT(get_table_clicked()));
    connect(my_button,SIGNAL(buttonClicked(int)),this,SLOT(btn_clicked(int)));

}

WaiterView::~WaiterView()
{
    delete ui;
}

/*槽函数*/

//服务开始
void WaiterView::service_begin_clicked()
{
    for(int i=0;i<3;i++)
    {
        if(table[i] != NULL)
        {
            //下单消息
            if(table[i]->getFinishOrder() == true)
            {
                //前台
                QString num = QString("%1").arg(table[i]->getTableNumber()+1);
                QMessageBox inform_box;
                inform_box.setFixedSize(400,200);
                inform_box.setWindowTitle("下单消息");
                inform_box.setIcon(QMessageBox::Information);
                num += "号客人已经下单!";
                inform_box.setText(num);
                inform_box.addButton("我知道了",QMessageBox::YesRole);

                QListWidgetItem *item = new QListWidgetItem();
                item->setText(num);
                ui->listWidget->addItem(item);
                my_button->button(i*5+1)->setStyleSheet("QWidget{border-image:url(:/img/red.png)}");
            }

            //催菜消息
            if(table[i]->getUrgeDishes() == true)
            {
                QString num = QString("%1").arg(table[i]->getTableNumber()+1);
                num += "号客人开始催菜!";
                QMessageBox::information(this,"催菜消息",num,QMessageBox::Yes);
                QListWidgetItem *item = new QListWidgetItem();
                item->setText(num);
                ui->listWidget->addItem(item);
                my_button->button(i*5+2)->setStyleSheet("QWidget{border-image:url(:/img/red.png)}");
            }

            //加水消息
            if(table[i]->getAddWater() == true)
            {
                QString num = QString("%1").arg(table[i]->getTableNumber()+1);
                num += "号客人要求加水!";
                QMessageBox::information(this,"加水消息",num,QMessageBox::Yes);
                QListWidgetItem *item = new QListWidgetItem();
                item->setText(num);
                ui->listWidget->addItem(item);
                my_button->button(i*5+3)->setStyleSheet("QWidget{border-image:url(:/img/red.png)}");
            }

            //结账消息
            if(table[i]->getCheckOut() == true)
            {
                QString num = QString("%1").arg(table[i]->getTableNumber()+1);
                num += "号客人要求结账!";
                QMessageBox::information(this,"结账消息",num, QMessageBox::Yes);
                QListWidgetItem *item = new QListWidgetItem();
                item->setText(num);
                ui->listWidget->addItem(item);
                my_button->button(i*5+4)->setStyleSheet("QWidget{border-image:url(:/img/red.png)}");
            }

            //叫服务员消息
            if(table[i]->getCallWaiter() == true)
            {
                QString num = QString("%1").arg(table[i]->getTableNumber()+1);
                num += "号客人要求服务";
                QMessageBox::information(this,"其他服务",num,QMessageBox::Yes);
                QListWidgetItem *item = new QListWidgetItem();
                item->setText(num);
                ui->listWidget->addItem(item);
                my_button->button(i*5+5)->setStyleSheet("QWidget{border-image:url(:/img/red.png)}");
            }

            //菜品完成消息
            for(int j=0;j<orderList.length();j++)
            {
                //如果有菜品完成
                if(orderList[j].getTableNumber() == table[i]->getTableNumber()
                        && orderList[j].getState() == "完成")
                {
                     QString inform = QString("%1号餐桌的").arg(orderList[j].getTableNumber()+1) +
                                     QString::fromStdString(orderList[j].getName()) + "已经做好";
                     QMessageBox::information(this,"准备上菜",inform,QMessageBox::Yes);
                }
            }
        }
    }
}


//选择新餐桌进行服务
void WaiterView::get_table_clicked()
{
    TableView *current_table_view = new TableView(this,NULL,waiter,"服务员");
    current_table_view->show();
    table_number++;
    this->hide();

}

//完成某项服务
void WaiterView::btn_clicked(int i)
{
     my_button->button(i)->setStyleSheet("QWidget{border-image:url(:/img/green.png)}");
}

//退出
void WaiterView::serve_end_clicked()
{
    this->hide();
    MainData m;
    m.dataOut();
}
