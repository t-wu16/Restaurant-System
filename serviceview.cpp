#include "serviceview.h"
#include "ui_serviceview.h"
extern QVector<Table> tableVector;
extern QList<Waiter> waiterList;
extern QList<Customer> customerList;

ServiceView::ServiceView(QWidget *parent, Customer *customer, Table *table) :
    QDialog(parent), customer(customer), table(table),
    ui(new Ui::ServiceView)
{
    ui->setupUi(this);
    setMinimumSize(1000,700);
    setMaximumSize(1000,700);
    setWindowTitle(tr("服务系统"));
    font1.setBold(true);
    font1.setPointSize(15);
    font2.setBold(true);
    font2.setPointSize(30);

    check_out_dialog = new QDialog(this);
    final_list = new QTableWidget(check_out_dialog);
    check_btn = new QPushButton("确认结账",check_out_dialog);
    cancle_btn = new QPushButton("取消结账",check_out_dialog);
    title = new QLabel("结算单",check_out_dialog);
    all_price_label = new QLabel("合计",check_out_dialog);
    all_price_edit = new QLineEdit(check_out_dialog);

    //绘制进度表
    table_dishes = new QTableWidget(this);
    table_dishes->setColumnCount(5);
    table_dishes->setRowCount(10);
    table_dishes->setHorizontalHeaderLabels(QStringList()<<"菜名"<<"类型"<<"数量"<<"备注"<<"进度");
    table_dishes->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中行的方式
    table_dishes->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    table_dishes->verticalHeader()->setVisible(false);                     //隐藏列表头
    table_dishes->setShowGrid(false);
    table_dishes->setGeometry(60,130,625,431);
    for(int i=0;i<5;i++)
    {
        table_dishes->setColumnWidth(i,121);
    }

    //显示数据
    map<Cuisine,int>::iterator iter;
    int row_now=0;
    for(iter=table->getFoodPlate().begin(); iter!=table->getFoodPlate().end(); iter++)
    {
        string name = iter->first.getName();
        string type = iter->first.getType();
        int num = iter->second;
        QString num_str = QString("%1").arg(num);
        string remark = iter->first.getRemark();
        string state = iter->first.getState();
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(name));
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(type));
        QTableWidgetItem *item2 = new QTableWidgetItem(num_str);
        QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString(remark));
        QTableWidgetItem *item4 = new QTableWidgetItem(QString::fromStdString(state));
        table_dishes->setItem(row_now, 0, item0);
        table_dishes->setItem(row_now, 1, item1);
        table_dishes->setItem(row_now, 2, item2);
        table_dishes->setItem(row_now, 3, item3);
        table_dishes->setItem(row_now, 4, item4);
        row_now++;
    }

    //积分按钮
    credit_show = new QPushButton(this);
    credit_show->setText(QString("$ %1").arg(customer->getCredit()));
    credit_show->setFont(font2);
    credit_show->setGeometry(400,300,200,100);
    credit_show->hide();

    //connect
    connect(ui->add_dishes,SIGNAL(clicked()),this,SLOT(addDishes_clicked()));
    connect(ui->urge_dishes,SIGNAL(clicked()),this,SLOT(urgeDishes_clicked()));
    connect(ui->add_water,SIGNAL(clicked()),this,SLOT(addWater_clicked()));
    connect(ui->check_out,SIGNAL(clicked()),this,SLOT(checkOut_clicked()));
    connect(ui->table_information,SIGNAL(clicked()),this,SLOT(getTable_clicked()));
    connect(ui->call_waiter,SIGNAL(clicked()),this,SLOT(callWaiter_clicked()));
    connect(ui->credit_btn,SIGNAL(clicked()),this,SLOT(credit_btn_clicked()));
    connect(check_btn,SIGNAL(clicked()),this,SLOT(confirm_clicked()));
    connect(ui->quit_btn,SIGNAL(clicked()),this,SLOT(quit_btn_clicked()));
    connect(credit_show,SIGNAL(clicked()),this,SLOT(credit_hide_clicked()));
    connect(cancle_btn,SIGNAL(clicked()),this,SLOT(cancle_btn_clicked()));
}

ServiceView::~ServiceView()
{
    delete ui;
}

//绘制结算单
void ServiceView::drawCheck()
{
    int money = table->checkOut();
    check_out_dialog->setMaximumSize(1000,700);
    check_out_dialog->setMinimumSize(1000,700);
    final_list->setGeometry(40,100,917,447);
    final_list->setColumnCount(6);
    final_list->setRowCount(11);
    final_list->setHorizontalHeaderLabels(QStringList()<<"编号"<<"菜名"<<"类型"<<
                                                        "单价"<<"数量"<<"合计");
    final_list->setSelectionBehavior(QAbstractItemView::SelectRows);     //单项选中的方式
    final_list->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    final_list->verticalHeader()->setVisible(false);                     //隐藏列表头
    for(int i=0;i<6;i++)
    {
        final_list->setColumnWidth(i,151);
    }

    //导入数据
    int i = 0;
    map<Cuisine,int>::iterator iter;
    for(iter=table->getFoodPlate().begin(); iter!=table->getFoodPlate().end(); iter++)
    {
        int number, price, all;
        const char *ch = iter->first.getId().c_str();
        QTableWidgetItem *item0 = new QTableWidgetItem(ch);
        final_list->setItem(i, 0, item0);

        ch = iter->first.getName().c_str();
        QTableWidgetItem *item1 = new QTableWidgetItem(ch);
        final_list->setItem(i, 1, item1);

        ch = iter->first.getType().c_str();
        QTableWidgetItem *item2 = new QTableWidgetItem(ch);
        final_list->setItem(i, 2, item2);

        price = iter->first.getPrice();
        QString str = QString("%1").arg(price);
        QTableWidgetItem *item3 = new QTableWidgetItem(str);
        final_list->setItem(i, 3, item3);

        number = iter->second;
        QString str2 = QString("%1").arg(number);
        QTableWidgetItem *item4 = new QTableWidgetItem(str2);
        final_list->setItem(i, 4, item4);

        all = number * price;
        QString str3 =QString("%1").arg(all);
        QTableWidgetItem *item5 = new QTableWidgetItem(str3);
        final_list->setItem(i, 5, item5);
        i++;
    }

    title->setFont(font2);
    title->setGeometry(370,20,261,61);
    all_price_label->setFont(font1);
    all_price_label->setGeometry(100,610,171,61);
    all_price_edit->setFont(font1);
    all_price_edit->setGeometry(280,610,171,61);
    check_btn->setFont(font1);
    check_btn->setGeometry(500,610,171,61);
    cancle_btn->setFont(font1);
    cancle_btn->setGeometry(730,610,171,61);

    QString str4 = QString("￥ %1").arg(money);
    all_price_edit->setText(str4);

    check_out_dialog->show();
}


/*槽函数*/

//加菜
void ServiceView::addDishes_clicked()
{
    QMessageBox question_box;
    question_box.setWindowTitle(tr("确认加菜"));
    question_box.setIcon(QMessageBox::Question);
    question_box.setText(tr("您需要继续点菜吗？"));
    QPushButton *yesBtn = question_box.addButton(tr("Yes"),QMessageBox::YesRole);
    QPushButton *noBtn = question_box.addButton(tr("No"),QMessageBox::NoRole);
    question_box.exec();

    if(question_box.clickedButton() == yesBtn)
    {
        CustomerView *customer_view = new CustomerView(this,customer,table);
        customer_view->show();
        this->hide();
    }
    if(question_box.clickedButton() == noBtn)
    {
        ;
    }
}

//催菜
void ServiceView::urgeDishes_clicked()
{
    //前台
    QMessageBox::information(this,tr("尊敬的顾客，您好！"),
                         tr("服务员将马上确认您的菜品状态，并尽快为您上菜，非常感谢"
                            "您的理解和支持"),QMessageBox::Yes);
    //后台
    table->urgeDishes();
}

//加水
void ServiceView::addWater_clicked()
{
    //前台
    QMessageBox::information(this,"尊敬的顾客，您好",
                             "服务员将马上为您加水，请您稍候片刻，"
                             "非常感谢您的理解和支持",QMessageBox::Yes);
    //后台
    table->addWater();
}

//查看餐桌
void ServiceView::getTable_clicked()
{
    TableView *current_table = new TableView(this,customer,NULL,"顾客");
    current_table->hideEdit();
    current_table->show();
}

//叫服务员
void ServiceView::callWaiter_clicked()
{
    QMessageBox::information(this,"尊敬的顾客，您好",
                             "您已召唤服务员，服务员将即刻来为您服务。",
                             QMessageBox::Yes);
    table->callWaiter();
}

//查看积分
void ServiceView::credit_btn_clicked()
{
    credit_show->show();
}

//退出积分
void ServiceView::credit_hide_clicked()
{
    credit_show->hide();
}

//退出
void ServiceView::quit_btn_clicked()
{
    this->hide();
    MainData m;
    m.dataOut();
}

//结账
void ServiceView::checkOut_clicked()
{
    //前台
    QMessageBox check_box;
    check_box.setWindowTitle(tr("确认结账"));
    check_box.setIcon(QMessageBox::Question);
    check_box.setText("尊敬的顾客，您好您已点击结账要求，确认我们将为您提供完整账单。");
    QPushButton *yesBtn = check_box.addButton(tr("确认"),QMessageBox::YesRole);
    QPushButton *noBtn = check_box.addButton(tr("取消"),QMessageBox::NoRole);
    check_box.exec();
    if(check_box.clickedButton() == yesBtn)
    {
        //显示账单
        this->hide();
        drawCheck();
    }
    if(check_box.clickedButton() == noBtn)
    {
        ;
    }
}


//确认结账
void ServiceView::confirm_clicked()
{
    check_out_dialog->hide();
    customer->addCredit(table->checkOut());
    Comment *comment = new Comment(this,customer,table);
    comment->show();
}

//取消结账
void ServiceView::cancle_btn_clicked()
{
    check_out_dialog->hide();
    this->show();
}
