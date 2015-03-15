#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("nutritioncalc.db");
    setTable();
}

void MainWindow::setTable(){
/*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("nutritioncalc");
        db.setUserName("nutrition");
        db.setPassword("nutrition");*/

        QString name;
        QString ia;
        QString ib;
        QString fat;
        qDebug() <<QCoreApplication::libraryPaths ();
        if (!db.open())
            qDebug() << "Failed to connect to root mysql admin";
        else{
            QSqlQuery q("select name,ingredient_a,ingredient_b,fat from fooddata",db);
            int count=0;
            ui->tableWidget_2->setRowCount(0);
            while (q.next()){

                ui->tableWidget_2->insertRow(count);
                name=q.value(0).toString(); // output all names
                ia = q.value(1).toString();
                ib = q.value(2).toString();
                fat = q.value(3).toString();
                ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(name));
                ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(ia));
                ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(ib));
                ui->tableWidget_2->setItem(count,3,new QTableWidgetItem(fat));
                count++;
            }

        }
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->userhight->text().isEmpty() || ui->userweight->text().isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("身高体重不能为空"),QMessageBox::Yes);
    }else{
        float weight = ui->userweight->text().toFloat();
        float height = ui->userhight->text().toFloat();
        float bmi=weight/(height*height)*10000.0;
        if (ui->lineEdit->text().isEmpty()){
            if(bmi>24&&bmi<=27.4){
                ui->textBrowser->setText(QString("您的体重过重，建议减肥!"));
            }else if(bmi>27.4){
                ui->textBrowser->setText(QString("胖的无可救药了!"));
            }else {
                ui->textBrowser->setText(QString("您的体重正常!"));
            }
        }else{

                QSqlQuery qsq("select ingredient_a,ingredient_b,fat from fooddata where name='"+ui->lineEdit->text()+"'");
                while(qsq.next()){
                    if(qsq.value(1).toFloat()<55&&qsq.value(2).toFloat()<10){
                        ui->textBrowser->setText(QString("推荐这种食物多吃"));

                    }else if(qsq.value(1).toFloat()>=55&&qsq.value(1).toFloat()<75&&qsq.value(2).toFloat()<10){
                        ui->textBrowser->setText(QString("这种食物可以吃，但不易多吃"));
                    }else if(qsq.value(1).toFloat()>=75&&qsq.value(2).toFloat()<10){
                        ui->textBrowser->setText(QString("这种食物尽量少吃"));
                    }else if(qsq.value(1).toFloat()<55&&qsq.value(2).toFloat()<20&&qsq.value(2).toFloat()>10){
                        ui->textBrowser->setText(QString("这种食物可以吃，但不易多吃"));
                    }else if(qsq.value(1).toFloat()>=75&&qsq.value(2).toFloat()<20&&qsq.value(2).toFloat()>10){
                        ui->textBrowser->setText(QString("这种食物少"));
                    }else if(qsq.value(1).toFloat()<=55&&qsq.value(2).toFloat()<20){
                        ui->textBrowser->setText(QString("这种食物少"));
                    }else if(qsq.value(1).toFloat()<=75&&qsq.value(1).toFloat()>55&&qsq.value(2).toFloat()<20){
                        ui->textBrowser->setText(QString("这种食物尽量少吃"));
                    }else if(qsq.value(1).toFloat()>=75&&qsq.value(2).toFloat()<20){
                        ui->textBrowser->setText(QString("这种食物一定少吃"));
                    }else{
                        ui->textBrowser->setText(QString("这种食物尽量少吃"));
                    }
            }

        }

    }
}
