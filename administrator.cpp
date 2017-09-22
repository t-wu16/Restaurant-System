#include "administrator.h"
#include "ui_administrator.h"
extern QList<Cuisine> menuList;

Administrator::Administrator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Administrator)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{border-image:url(:/img/background.jpg)}");

    hideAll();
}

Administrator::~Administrator()
{
    delete ui;
}

//隐藏管理界面
void Administrator::hideAll()
{
    //通用控件
    ui->menuView->hide();
    ui->peopleView->hide();
    ui->peopleView->hide();
    ui->commit_btn->hide();
    ui->revert_btn->hide();
    ui->select_btn->hide();
    ui->select_btn_2->hide();
    ui->showall_btn->hide();
    ui->showall_btn_2->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->back->hide();
    ui->change_btn->hide();

    //菜单控件
    ui->add_btn->hide();
    ui->delete_btn->hide();
    ui->id_edit->hide();
    ui->name_edit->hide();
    ui->price_edit->hide();
    ui->type_edit->hide();
    ui->frame->hide();
    ui->confirm_btn->hide();
    ui->cancle_btn->hide();

    //账户控件
    ui->add_btn_2->hide();
    ui->delete_btn_2->hide();
    ui->id_edit_2->hide();
    ui->name_edit_2->hide();
    ui->password_edit->hide();
    ui->identity_edit->hide();
    ui->frame_2->hide();
    ui->confirm_btn_2->hide();
    ui->cancle_btn_2->hide();

}

//显示菜单管理界面
void Administrator::showMenu()
{
    ui->menuView->show();
    ui->commit_btn->show();
    ui->revert_btn->show();
    ui->delete_btn->show();
    ui->add_btn->show();
    ui->select_btn->show();
    ui->select_btn_2->show();
    ui->showall_btn->show();
    ui->back->show();
    ui->change_btn->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
}

//显示账户管理界面
void Administrator::showPeople()
{
    ui->peopleView->show();
    ui->commit_btn->show();
    ui->revert_btn->show();
    ui->delete_btn_2->show();
    ui->add_btn_2->show();
    ui->select_btn->show();
    ui->select_btn_2->show();
    ui->showall_btn_2->show();
    ui->back->show();
    ui->change_btn->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
}

/*槽函数*/

//菜单管理
void Administrator::on_menu_btn_clicked()
{

    showMenu();
    model = new QSqlTableModel(this);
    model->setTable("menu");
    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"菜名");
    model->setHeaderData(2,Qt::Horizontal,"价格");
    model->setHeaderData(3,Qt::Horizontal,"类型");
    model->setHeaderData(4,Qt::Horizontal,"好评数");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->menuView->setModel(model);                                         //关联数据库与显示表
    ui->menuView->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
    ui->menuView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->menuView->verticalHeader()->setVisible(false);                     //隐藏列表头
    ui->menuView->setShowGrid(false);                                      //不显示格子线
    for(int i=0;i<5;i++)
    {
        ui->menuView->setColumnWidth(i,150);
    }

}

//人员管理
void Administrator::on_people_btn_clicked()
{
    showPeople();
    model = new QSqlTableModel(this);
    model->setTable("people");
    model->setHeaderData(0,Qt::Horizontal,"账号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"密码");
    model->setHeaderData(3,Qt::Horizontal,"身份");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->peopleView->setModel(model);
    ui->peopleView->setSelectionBehavior(QAbstractItemView::SelectRows);     //整行选中的方式
    ui->peopleView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->menuView->verticalHeader()->setVisible(false);                     //隐藏列表头
    ui->menuView->setShowGrid(false);                                      //不显示格子线
    for(int i=0;i<4;i++)
    {
        ui->peopleView->setColumnWidth(i,183);
    }
}

//修改内容
void Administrator::on_change_btn_clicked()
{
    ui->menuView->setEditTriggers(QAbstractItemView::AllEditTriggers);      //允许修改
    ui->peopleView->setEditTriggers(QAbstractItemView::AllEditTriggers);    //允许修改
}

//提交修改
void Administrator::on_commit_btn_clicked()
{
    ui->menuView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    ui->peopleView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //禁止修改
    model->database().transaction();        //开始事物操作
    if(model->submitAll())
    {
        model->database().commit();         //提交
    }
    else
    {
        model->database().rollback();       //回滚
        QMessageBox::warning(this, tr("tableModel"),
                                    tr("数据库错误: %1")
                                    .arg(model->lastError().text()));
    }
}

//撤销修改
void Administrator::on_revert_btn_clicked()
{
    model->revertAll();
}

//删除旧项(菜单)
void Administrator::on_delete_btn_clicked()
{
    int curRow = ui->menuView->currentIndex().row();
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
       model->revertAll(); //如果不删除，则撤销
    }
    else model->submitAll(); //否则提交，在数据库中删除该行
}

//删除旧项(人员)
void Administrator::on_delete_btn_2_clicked()
{
    int curRow = ui->peopleView->currentIndex().row();
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
    {
       model->revertAll(); //如果不删除，则撤销
    }
    else model->submitAll(); //否则提交，在数据库中删除该行
}

//查询名字
void Administrator::on_select_btn_clicked()
{
    QString name = ui->lineEdit->text();
    model->setFilter(QString("name = '%1'").arg(name));
    model->select();
}

//查询类型
void Administrator::on_select_btn_2_clicked()
{
    QString type = ui->lineEdit_2->text();
    model->setFilter(QString("type = '%1'").arg(type));
    model->select();
}

//显示全表(菜单)
void Administrator::on_showall_btn_clicked()
{
    model->setTable("menu");
    model->select();
}

//显示全表(账户)
void Administrator::on_showall_btn_2_clicked()
{
    model->setTable("people");
    model->select();
}

//添加新项（菜单）
void Administrator::on_add_btn_clicked()
{
    ui->id_edit->show();
    ui->name_edit->show();
    ui->price_edit->show();
    ui->type_edit->show();
    ui->frame->show();
    ui->confirm_btn->show();
    ui->cancle_btn->show();
}

//菜单确定添加
void Administrator::on_confirm_btn_clicked()
{
    int rowNum = model->rowCount();               //当前数据的行数
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),ui->id_edit->text());
    model->setData(model->index(rowNum,1),ui->name_edit->text());
    model->setData(model->index(rowNum,2),ui->price_edit->text().toInt());
    model->setData(model->index(rowNum,3),ui->type_edit->text());
    ui->id_edit->hide();
    ui->name_edit->hide();
    ui->price_edit->hide();
    ui->type_edit->hide();
    ui->frame->hide();
    ui->confirm_btn->hide();
    ui->cancle_btn->hide();
    //清空文本框
    ui->id_edit->clear();
    ui->name_edit->clear();
    ui->price_edit->clear();
    ui->type_edit->clear();
}

//菜单取消添加
void Administrator::on_cancle_btn_clicked()
{
    ui->id_edit->hide();
    ui->name_edit->hide();
    ui->price_edit->hide();
    ui->type_edit->hide();
    ui->frame->hide();
    ui->confirm_btn->hide();
    ui->cancle_btn->hide();
}

//添加新项（人员）
void Administrator::on_add_btn_2_clicked()
{
    ui->id_edit_2->show();
    ui->name_edit_2->show();
    ui->password_edit->show();
    ui->identity_edit->show();
    ui->frame_2->show();
    ui->confirm_btn_2->show();
    ui->cancle_btn_2->show();
    //清空文本框
    ui->id_edit_2->clear();
    ui->name_edit_2->clear();
    ui->password_edit->clear();
    ui->identity_edit->clear();
}

//人员确定添加
void Administrator::on_confirm_btn_2_clicked()
{
    int rowNum = model->rowCount();               //当前数据的行数
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0),ui->id_edit_2->text());
    model->setData(model->index(rowNum,1),ui->name_edit_2->text());
    model->setData(model->index(rowNum,2),ui->password_edit->text().toInt());
    model->setData(model->index(rowNum,3),ui->identity_edit->text());
    ui->id_edit_2->hide();
    ui->name_edit_2->hide();
    ui->password_edit->hide();
    ui->identity_edit->hide();
    ui->frame_2->hide();
    ui->confirm_btn_2->hide();
    ui->cancle_btn_2->hide();
}

//人员取消添加
void Administrator::on_cancle_btn_2_clicked()
{
    ui->id_edit_2->hide();
    ui->name_edit_2->hide();
    ui->password_edit->hide();
    ui->identity_edit->hide();
    ui->frame_2->hide();
    ui->confirm_btn_2->hide();
    ui->cancle_btn_2->hide();
}

//返回
void Administrator::on_back_clicked()
{
    hideAll();
}


void Administrator::on_pushButton_clicked()
{
    this->hide();
}
