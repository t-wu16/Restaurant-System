#include "comment.h"
#include "ui_comment.h"

extern QList<Cuisine> menuList;
extern QVector<Table> tableVector;
extern QList<Waiter> waiterList;
extern QList<Customer> customerList;

Comment::Comment(QWidget *parent, Customer *customer, Table *table) :
    QDialog(parent), customer(customer), table(table),
    ui(new Ui::Comment)
{
    ui->setupUi(this);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);
    this->setWindowTitle("评价系统");
    QFont font1;
    font1.setPointSize(13);
    font1.setBold(true);
    QFont font2;
    font2.setPointSize(20);
    font2.setBold(true);

    comment_dialog = new QDialog(this);
    comment_list = new QTableWidget(this);
    praise_btn = new QButtonGroup(this);
    waiter_comment_btn = new QButtonGroup(this);
    finish_comment_btn = new QPushButton("完成评价",this);
    waiter_label = new QLabel("服务员评分",this);
    waiter_label->setFont(font1);
    waiter_label->setGeometry(60,70,150,50);
    title_label = new QLabel("评价系统",this);
    title_label->setFont(font2);
    title_label->setGeometry(430,5,620,75);

    comment_dialog->setMinimumSize(1000,700);
    comment_dialog->setMaximumSize(1000,700);
    comment_list->setColumnCount(4);
    comment_list->setRowCount(10);
    comment_list->setHorizontalHeaderLabels(QStringList()<<"菜名"<<"类型"<<"价格"<<"好评");
    comment_list->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中行的方式
    comment_list->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    comment_list->verticalHeader()->setVisible(false);                     //隐藏列表头
    comment_list->setShowGrid(false);
    comment_list->setGeometry(60,150,750,431);
    for(int i=0;i<4;i++)
    {
        comment_list->setColumnWidth(i,172);
    }
    map<Cuisine,int>::iterator iter;
    int row_now=0;
    for(iter=table->getFoodPlate().begin(); iter!=table->getFoodPlate().end(); iter++)
    {
        string name = iter->first.getName();
        string type = iter->first.getType();
        int num = iter->second;
        QString num_str = QString("%1").arg(num);
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::fromStdString(name));
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(type));
        QTableWidgetItem *item2 = new QTableWidgetItem(num_str);
        comment_list->setItem(row_now, 0, item0);
        comment_list->setItem(row_now, 1, item1);
        comment_list->setItem(row_now, 2, item2);
        QPushButton *btn = new QPushButton("好评",this);
        btn->setFont(font1);
        comment_list->setCellWidget(row_now, 3, btn);
        praise_btn->addButton(btn,row_now);
        row_now++;
    }

    for(int i=0;i<5;i++)
    {
        QPushButton *btn = new QPushButton(this);
        waiter_comment_btn->addButton(btn,i);
        waiter_comment_btn->button(i)->setGeometry(235+100*i,70,80,50);
        waiter_comment_btn->button(i)->show();
    }
    waiter_comment_btn->button(0)->setText("1");
    waiter_comment_btn->button(1)->setText("2");
    waiter_comment_btn->button(2)->setText("3");
    waiter_comment_btn->button(3)->setText("4");
    waiter_comment_btn->button(4)->setText("5");


    finish_comment_btn->setGeometry(800,600,150,80);

    //connect
    connect(praise_btn,SIGNAL(buttonClicked(int)),this,SLOT(praise_btn_clicked(int)));
    connect(finish_comment_btn,SIGNAL(clicked()),this,SLOT(finish_comment_btn_clicked()));
    connect(waiter_comment_btn,SIGNAL(buttonClicked(int)),this,SLOT(waiter_comment_btn_clicked(int)));
}

Comment::~Comment()
{
    delete ui;
}

/*槽函数*/

//点击好评
void Comment::praise_btn_clicked(int i)
{
    QMessageBox::information(this,"评价","谢谢您的好评,欢迎再次光临",QMessageBox::Yes);
    //从menuList中找到这道菜
    for(int j=0;j<menuList.length();j++)
    {
        if(comment_list->item(i,0)->text() == QString::fromStdString(menuList[j].getName()))
        {
            //该道菜的好评数+1
            menuList[j].setPraise();
        }
    }
}

//评价服务员
void Comment::waiter_comment_btn_clicked(int i)
{
    QMessageBox::information(this,"评价","谢谢您的评价,欢迎再次光临",QMessageBox::Yes);
    for(int j=0;j<waiterList.length();j++)
    {
        if(waiterList[j].getId() == table->getWaiterId())
        {
            waiterList[j].addCommentTimes();
            waiterList[j].addCommentScore(i+1);
            break;
        }
    }
}

//完成评价
void Comment::finish_comment_btn_clicked()
{
    this->hide();
    MainData m;
    m.dataOut();
}
