#include "mainwindow.h"
#include "ui_mainwindow.h"

extern  BaseSet bs;


void MainWindow::set_ext_osk_1(bool b){

}
void MainWindow::set_osk_1(bool b){

}
void MainWindow::set_ext_pin_osk_1(bool b){

}
void MainWindow::refresh_com_list(){
    ui->com_list->clear();
    auto ls = bs.com_list();
    for(int i=0;i<ls.size();++i)
        ui->com_list->insertItem(i,tr(ls[i].c_str()));
}

void MainWindow::ini_1(){
    connect(ui->refresh_com,SIGNAL(clicked(bool)),this,SLOT(refresh_com_list()));
}
