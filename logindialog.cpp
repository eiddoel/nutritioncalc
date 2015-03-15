#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);

}

loginDialog::~loginDialog()
{
    delete ui;
}


void loginDialog::on_loginBtn_clicked()
{
    //QcoreApplication::addLibraryPath("/home/eiddoel/Qt5.3.2/5.3/gcc_64/plugins/sqldrivers");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","mysqlite");
        //db.setHostName("127.0.0.1");
        db.setDatabaseName("nutritioncalc.db");
        //db.setUserName("nutrition");
        //db.setPassword("nutrition");
        //qDebug() <<QCoreApplication::libraryPaths ();
        if (!db.open())
            qDebug() << "Failed to connect to root mysql admin";
        else{
            QSqlQuery q("select user_name,user_password from user where user_Name='"+ui->username->text()+"'",db);
            //QSqlRecord rec = q.record();

            //qDebug() << "Number of columns: " << rec.count();

            //int nameCol = rec.indexOf("name"); // index of the field "name"
            qDebug()<<ui->username->text();
            qDebug()<<ui->password->text();
            QString pwd;

            while (q.next()){
                pwd=q.value(1).toString(); // output all names
                qDebug()<<"数据库的密码是:"<<pwd;
            }
            if(!ui->password->text().isEmpty()&&ui->password->text()==pwd) {
                accept();//判断用户名和密码是否正确
            }else{
                QMessageBox::warning(this,tr("警告"),tr("用户名密码错误"),QMessageBox::Yes);
            }


        }


}
