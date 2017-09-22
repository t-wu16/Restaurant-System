#include "tableview.h"
#include "ui_tableview.h"
extern QVector<Table> tableVector;

TableView::TableView(QWidget *parent, Customer *customer, Waiter *waiter,
                     const std::string &identity) :
    QDialog(parent),customer(customer),waiter(waiter),identity(identity),
    ui(new Ui::TableView)
{
    initTable();
    ui->setupUi(this);
    this->setMinimumSize(755,479);
    this->setMaximumSize(755,479);
    this->setWindowTitle("餐桌实时信息");

    font1.setPointSize(15);
    font1.setBold(true);
    font2.setPointSize(12);
    font2.setBold(true);

    table_edit = new QLineEdit(this);
    table_edit->setFont(font1);
    table_edit->setFocus();
    table_edit->setGeometry(615,320,130,51);

    choose_table = new QPushButton(this);
    choose_table->setGeometry(620,400,121,61);
    choose_table->setFont(font2);
    choose_table->setText("开始点菜");
    serve_table = new QPushButton(this);
    serve_table->setGeometry(620,400,121,61);
    serve_table->setFont(font2);
    serve_table->setText("开始服务");

    setTableBackground();

    if(identity == "顾客")
    {
        choose_table->show();
        serve_table->hide();
    }
    if(identity == "服务员")
    {
        serve_table->show();
        choose_table->hide();
    }

    //connect
    connect(choose_table,SIGNAL(clicked()),this,SLOT(on_choose_table_clicked()));
    connect(serve_table,SIGNAL(clicked()),this,SLOT(on_serve_table_clicked()));
    connect(ui->quit_btn,SIGNAL(clicked()),this,SLOT(on_quit_btn_clicked()));
}

TableView::~TableView()
{
    delete ui;
}


void TableView::initTable()
{
    table = &tableVector[0];        //将全局变量的首地址赋给Table指针，通过table来操作tableVector的内容。
}

Table* TableView::getTable()
{
    return table;
}

//隐藏顾客输入框
void TableView::hideEdit()
{
    table_edit->hide();
    choose_table->hide();
    serve_table->hide();
    ui->label_4->hide();
}

//绘制餐桌背景
void TableView::setTableBackground()
{
    button_group = new QButtonGroup(this);
    button_group->addButton(ui->table1,1);
    button_group->addButton(ui->table2,2);
    button_group->addButton(ui->table3,3);
    button_group->addButton(ui->table4,4);
    button_group->addButton(ui->table5,5);
    button_group->addButton(ui->table6,6);
    button_group->addButton(ui->table7,7);
    button_group->addButton(ui->table8,8);
    button_group->addButton(ui->table9,9);
    button_group->addButton(ui->table10,10);
    button_group->addButton(ui->table11,11);
    button_group->addButton(ui->table12,12);
    button_group->addButton(ui->table13,13);
    button_group->addButton(ui->table14,14);
    button_group->addButton(ui->table15,15);
    button_group->addButton(ui->table16,16);
    for(int i=0;i<16;i++)
    {
        if(table[i].getWaiterId() == "" && table[i].getCustomerId() != "")        //如果桌子有顾客但没有服务员
        {
            button_group->button(i+1)->setStyleSheet("background-color: rgb(170,0,0);"
                                                     "border-image:url(:/img/table.png)");
        }
        if(table[i].getState() == unoccupied)   //如果桌子已空
        {
            button_group->button(i+1)->setStyleSheet("border-image:url(:/img/table.png)");
        }
    }
}

/*槽函数*/

//选桌按钮
void TableView::on_choose_table_clicked()
{
    int k=table_edit->text().toInt();
    if((k>0 && k<17 && table[k-1].getState()==unoccupied))
    {
        //改变顾客所选餐桌的信息和顾客的信息
        table[k-1].setCustomerId(customer->getId());
        table[k-1].setState(order);
        customer->setTableNumber(k-1);      //顾客选桌
        customer_view = new CustomerView(this,customer,&table[k-1]);
        this->hide();
        customer_view->show();
    }
    else
    {
        QMessageBox::warning(this,tr("选桌失败"),
                             tr("请您选择空闲的餐桌"),
                             QMessageBox::Yes);
    }
}


//开始服务
void TableView::on_serve_table_clicked()
{
    int m = waiter->getServeNum();          //服务数量
    int k = table_edit->text().toInt();     //服务桌号（显示）
    if(k>0 && k<17 && table[k-1].getWaiterId()=="")
    {
        table[k-1].setWaiterId(waiter->getId());
        waiter->setTableNumber(k,m);            //服务员认领她服务的第m+1个餐桌，桌号为k
        waiter_view = new WaiterView(this,waiter,&table[k-1]);
        waiter_view->show();
        this->hide();

    }
    else
    {
        QMessageBox::warning(this,tr("Warninig"),
                             tr("Please choose right table!"),
                             QMessageBox::Yes);
    }
}

//退出按钮
void TableView::on_quit_btn_clicked()
{
    MainData m;
    m.dataOut();
    this->hide();
}


