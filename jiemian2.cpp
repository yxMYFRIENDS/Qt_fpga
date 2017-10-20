#include "mainwindow.h"
#include "ui_mainwindow.h"

extern Sweep sweep;
extern CurrentState cs;



void MainWindow::set_io_update(bool b){
    cout<<"11"<<endl;
    cs.io_update();
}

void MainWindow::set_enable_sweep(bool b){
    sweep.enable(b);
    sweep.set_mode(0);
}
void MainWindow::set_enable_frequency_jump(bool b){
    sweep.enable_fj(b);
}
void MainWindow::set_drctl(bool b){
    sweep.set_drctl(b);
}
void MainWindow::set_auto_drctl(bool b){
    sweep.set_auto_drctl(b);
}
void MainWindow::set_Dwell_Low(bool b){
    sweep.set_Dwell_Low(b);
}
void MainWindow::set_Dwell_High(bool b){
    sweep.set_Dwell_High(b);
}
void MainWindow::change_value_0(QString s){
    sweep.change_value(0,s.toDouble());
}
void MainWindow::change_value_1(QString s){
    sweep.change_value(1,s.toDouble());
}
void MainWindow::change_value_2(QString s){
    sweep.change_value(2,s.toDouble());
}
void MainWindow::change_value_3(QString s){
    sweep.change_value(3,s.toDouble());
}
void MainWindow::change_value_4(QString s){
    sweep.change_value(4,s.toDouble());
}
void MainWindow::change_value_5(QString s){
    sweep.change_value(5,s.toDouble());
}
void MainWindow::change_value_6(QString s){
    sweep.change_value(6,s.toDouble());
}
void MainWindow::change_value_7(QString s){
    sweep.change_value(7,s.toDouble());
}

void MainWindow::ini_2(){
    connect(ui->set_drctl,SIGNAL(clicked(bool)),this,SLOT(set_drctl(bool)));
    connect(ui->set_auto_drctl,SIGNAL(clicked(bool)),this,SLOT(set_auto_drctl(bool)));
    connect(ui->set_enable_sweep,SIGNAL(clicked(bool)),this,SLOT(set_enable_sweep(bool)));
    connect(ui->set_enable_frequency_jump,SIGNAL(clicked(bool)),this,SLOT(set_enable_frequency_jump(bool)));
    connect(ui->set_io_update,SIGNAL(clicked(bool)),this,SLOT(set_io_update(bool)));
    connect(ui->set_dewll_high,SIGNAL(clicked(bool)),this,SLOT(set_Dwell_High(bool)));
    connect(ui->set_dwell_low,SIGNAL(clicked(bool)),this,SLOT(set_Dwell_Low(bool)));
    connect(ui->change_value_0,SIGNAL(textChanged(QString)),this,SLOT(change_value_0(QString)));
    connect(ui->change_value_1,SIGNAL(textChanged(QString)),this,SLOT(change_value_1(QString)));
    connect(ui->change_value_2,SIGNAL(textChanged(QString)),this,SLOT(change_value_2(QString)));
    connect(ui->change_value_3,SIGNAL(textChanged(QString)),this,SLOT(change_value_3(QString)));
    connect(ui->change_value_4,SIGNAL(textChanged(QString)),this,SLOT(change_value_4(QString)));
    connect(ui->change_value_5,SIGNAL(textChanged(QString)),this,SLOT(change_value_5(QString)));
    connect(ui->change_value_6,SIGNAL(textChanged(QString)),this,SLOT(change_value_6(QString)));
    connect(ui->change_value_7,SIGNAL(textChanged(QString)),this,SLOT(change_value_7(QString)));
    refresh_2();
}
void MainWindow::refresh_2(){

}
