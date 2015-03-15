#include "mainwindow.h"
#include <QApplication>

#include <logindialog.h>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    loginDialog *login = new loginDialog();
    QDesktopWidget *desktop=QApplication::desktop();
       //获取桌面宽度
       int w=desktop->width();
      //获取桌面高度
       int h=desktop->height();

       //居中显示
       window.move((w-window.width())/2,(h-window.height())/2);


    if(login->exec() == QDialog::Accepted){

        window.show();
        return a.exec();
    }else{
        return -1;
    }

}
