#include "customerview.h"

extern QVector<Table> tableVector;
CustomerView::CustomerView(QWidget *parent, Customer *customer, Table *table) :
     QDialog(parent), customer(customer), table(table)
{
    menu_row = -1;
    plate_row = -1;
    plate_row_now = 0;
    dish_number = 0;
    this->drawOrder();
    this->drawNumber();
    number->hide();

    //connect
    connect(menu_list,SIGNAL(clicked(QModelIndex)),this,SLOT(get_menu_item()));     //获取点击内容
    connect(plate_list,SIGNAL(clicked(QModelIndex)),this,SLOT(get_plate_item()));
    connect(add_btn,SIGNAL(clicked()),this,SLOT(add_btn_clicked()));
    connect(delete_btn,SIGNAL(clicked()),this,SLOT(delete_btn_clicked()));
    connect(confirm_btn,SIGNAL(clicked()),this,SLOT(number_btn_clicked()));
    connect(cancle_btn,SIGNAL(clicked()),this,SLOT(cancle_btn_clicked()));
    connect(finish_btn,SIGNAL(clicked()),this,SLOT(finish_btn_clicked()));

}

CustomerView::~CustomerView()
{
    delete nLayout;
}

Customer* CustomerView::getCustomer()
{
    return customer;
}

//绘制点菜界面
void CustomerView::drawOrder()
{
    setMinimumSize(1000,700);
    setMaximumSize(1000,700);
    setWindowTitle(tr("欢迎光临"));
    this->setStyleSheet("QDialog{border-image:url(:/img/background2.jpg)}");

    font1.setPointSize(14);
    font1.setBold(true);
    font2.setPointSize(10);
    font2.setBold(true);

    QIcon add_icon(":/img/add.png");
    add_btn = new QPushButton(this);
    add_btn->setIcon(add_icon);
    add_btn->setIconSize(QSize(70,70));
    add_btn->setFlat(true);
    add_btn->setGeometry(460,340,93,71);

    QIcon delete_icon(":/img/delete.png");
    delete_btn = new QPushButton(this);
    delete_btn->setIcon(delete_icon);
    delete_btn->setIconSize(QSize(70,70));
    delete_btn->setFlat(true);
    delete_btn->setGeometry(460,520,93,71);

    QIcon finish_icon(":/img/finish.png");
    finish_btn = new QPushButton(this);
    finish_btn->setFont(font1);
    finish_btn->setIcon(finish_icon);
    finish_btn->setIconSize(QSize(100,100));
    finish_btn->setFlat(true);
    finish_btn->setGeometry(830,50,141,100);

    menu_label = new QLabel("菜单",this);
    menu_label->setFont(font1);
    menu_label->setGeometry(200,30,111,31);
    plate_label = new QLabel("食物托盘",this);
    plate_label->setFont(font1);
    plate_label->setGeometry(730,150,111,41);

    id_label = new QLabel("手机号",this);
    id_label->setFont(font1);
    id_label->setGeometry(560,50,91,41);
    const char *ch1 = customer->getId().c_str();
    id_text = new QLabel(ch1,this);
    id_text->setFont(font1);
    id_text->setGeometry(650,50,151,41);


    name_label = new QLabel("尊敬的",this);
    name_label->setFont(font1);
    name_label->setGeometry(560,100,91,41);
    const char *ch2 = customer->getName().c_str();
    name_text = new QLabel(ch2,this);
    name_text->setFont(font1);
    name_text->setGeometry(650,100,121,41);

    //绑定菜单与视图
    model = new QSqlTableModel(this);
    model->setTable("menu");
    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"菜名");
    model->setHeaderData(2,Qt::Horizontal,"价格");
    model->setHeaderData(3,Qt::Horizontal,"类型");
    model->setHeaderData(4,Qt::Horizontal,"好评数");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    menu_list = new QTableView(this);
    menu_list->setModel(model);
    menu_list->setGeometry(20,80,431,581);
    menu_list->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
    menu_list->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    menu_list->verticalHeader()->setVisible(false);                     //隐藏列表头
    menu_list->setShowGrid(false);                                      //不显示格子线
    menu_list->setColumnWidth(0,77);
    menu_list->setColumnWidth(3,100);
    menu_list->setStyleSheet("QWidget(border-image:url(:/img/background2.jpg))");

    //设置食物托盘样式
    plate_list = new QTableWidget(this);
    plate_list->setStyleSheet("QWidget(border-image:url(:/img/background2.jpg))");
    plate_list->setGeometry(570,200,411,461);
    plate_list->setColumnCount(6);
    plate_list->setRowCount(8);
    plate_list->setHorizontalHeaderLabels(QStringList()<<"编号"<<"菜名"<<"类型"<<
                                                        "单价"<<"数量"<<"备注");
    plate_list->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
    plate_list->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    plate_list->verticalHeader()->setVisible(false);                     //隐藏列表头
    plate_list->setShowGrid(false);
    for(int i=0;i<5;i++)
    {
        plate_list->setColumnWidth(i,60);
    }
    plate_list->setColumnWidth(5,102);

}

//绘制数量选择框
void CustomerView::drawNumber()
{
    number_label = new QLabel("数量:",this);
    number_label->setFont(font1);
    number_edit = new QLineEdit(this);
    number_edit->setFont(font1);

    remark_label = new QLabel("备注:",this);
    remark_label->setFont(font1);
    remark_edit = new QLineEdit(this);
    remark_edit->setFont(font1);

    confirm_btn = new QPushButton("确定",this);
    confirm_btn->setFont(font1);
    cancle_btn = new QPushButton("取消",this);
    cancle_btn->setFont(font1);

    number = new QDialog(this);
    number->setWindowTitle("数量");
    number->setFixedSize(220,200);
    nLayout = new QGridLayout();
    nLayout->addWidget(number_label,0,0);
    nLayout->addWidget(number_edit,0,1);
    nLayout->addWidget(remark_label,1,0);
    nLayout->addWidget(remark_edit,1,1);
    nLayout->addWidget(confirm_btn,2,0);
    nLayout->addWidget(cancle_btn,2,1);
    number->setLayout(nLayout);
}


/*槽函数*/

//获取菜单行内容
void CustomerView::get_menu_item()
{
    //应该根据菜的行号获取菜的信息
    menu_row = menu_list->currentIndex().row();
    QModelIndex mdlIndex0 = menu_list->currentIndex().sibling(menu_row,0);
    QModelIndex mdlIndex1 = menu_list->currentIndex().sibling(menu_row,1);
    QModelIndex mdlIndex2 = menu_list->currentIndex().sibling(menu_row,2);
    QModelIndex mdlIndex3 = menu_list->currentIndex().sibling(menu_row,3);
    menu_id = model->data(mdlIndex0,Qt::DisplayRole).toString();
    menu_name = model->data(mdlIndex1,Qt::DisplayRole).toString();
    menu_price = model->data(mdlIndex2,Qt::DisplayRole).toInt();
    menu_type = model->data(mdlIndex3,Qt::DisplayRole).toString();

}

//获取托盘行内容
void CustomerView::get_plate_item()
{
    plate_row = plate_list->currentRow();
    plate_id = plate_list->item(plate_row,0)->text();
    plate_name = plate_list->item(plate_row,1)->text();
    plate_type = plate_list->item(plate_row,2)->text();
    plate_number = plate_list->item(plate_row,4)->text().toInt();
    plate_price = plate_list->item(plate_row,3)->text().toInt();
    remark = plate_list->item(plate_row,4)->text().toStdString();
}

//添加按钮槽函数
void CustomerView::add_btn_clicked()
{
    if(menu_row != -1)                       //如果获取到了行内容，就选择数量
    {
        //弹出数量选择框
        number->show();
        number_edit->setFocus();
    }
}

//选择数量槽函数
void CustomerView::number_btn_clicked()
{
    //界面显示
    dish_number = number_edit->text().toInt();
    if(dish_number > 0)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem(menu_id);
        QTableWidgetItem *item1 = new QTableWidgetItem(menu_name);
        QTableWidgetItem *item2 = new QTableWidgetItem(menu_type);
        QTableWidgetItem *item3 = new QTableWidgetItem(QString("%1").arg(menu_price));
        QTableWidgetItem *item4 = new QTableWidgetItem(number_edit->text());
        QTableWidgetItem *item5 = new QTableWidgetItem(remark_edit->text());
        plate_list->setItem(plate_row_now, 0, item0);
        plate_list->setItem(plate_row_now, 1, item1);
        plate_list->setItem(plate_row_now, 2, item2);
        plate_list->setItem(plate_row_now, 3, item3);
        plate_list->setItem(plate_row_now, 4, item4);
        plate_list->setItem(plate_row_now, 5, item5);
        plate_row_now++;
        number->hide();
        //后台操作
        //创建Cuisine对象，然后将该对象添加到食物托盘
        Cuisine food(menu_id.toStdString(), menu_name.toStdString(),menu_price,
                     menu_type.toStdString(),remark_edit->text().toStdString());
        table->chooseFood(food, dish_number);

        //清空文本框
        number_edit->clear();
        remark_edit->clear();
    }
}

//取消选择
void CustomerView::cancle_btn_clicked()
{
    number->hide();
}

//删除按钮槽函数
void CustomerView::delete_btn_clicked()
{
    if(plate_row != -1)
    {
        QMessageBox question_box;
        question_box.setWindowTitle(tr("是否确认"));
        question_box.setIcon(QMessageBox::Question);
        question_box.setText(tr("您确定要删除该菜品？"));
        QPushButton *yesBtn = question_box.addButton(tr("Yes"),QMessageBox::YesRole);
        QPushButton *noBtn = question_box.addButton(tr("No"),QMessageBox::NoRole);
        question_box.exec();

        if(question_box.clickedButton() == yesBtn)
        {
            plate_list->removeRow(plate_row);
            //创建该菜品对象，并将其数量设为0
            Cuisine food(plate_id.toStdString(), plate_name.toStdString(),
                         plate_price, plate_type.toStdString());
            table->chooseFood(food,-plate_number);

        }
        if(question_box.clickedButton() == noBtn)
        {
            ;
        }
        plate_row_now--;
    }
}


//下单槽函数
void CustomerView::finish_btn_clicked()
{
    QMessageBox question_box;
    question_box.setWindowTitle(tr("确认下单"));
    question_box.setIcon(QMessageBox::Question);
    question_box.setText(tr("您已选好了心意的菜品吗？"));
    QPushButton *yesBtn = question_box.addButton(tr("Yes"),QMessageBox::YesRole);
    QPushButton *noBtn = question_box.addButton(tr("No"),QMessageBox::NoRole);
    question_box.exec();

    if(question_box.clickedButton() == yesBtn)
    {
        table->orderFinish();           //后台下单
        this->hide();
        service_view = new ServiceView(this,customer,table);
        service_view->show();
    }
    if(question_box.clickedButton() == noBtn)
    {
        ;
    }
}
