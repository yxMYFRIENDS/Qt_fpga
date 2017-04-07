#include "mainwindow.h"
#include "ui_mainwindow.h"

extern  BaseSet bs;

void MainWindow::set_ext_osk_1(bool b){
    bs.set_external_oskenable(b);
}
void MainWindow::set_osk_1(bool b){
    bs.set_osk_enable(b);
}
void MainWindow::set_ext_pin_osk_1(bool b){
    bs.get_cur_state().set_osk(b);
}
void MainWindow::refresh_com_list_1(){
    ui->com_list->clear();
    auto ls = bs.com_list();
    for(int i=0;i<ls.size();++i)
        ui->com_list->insertItem(i,tr(ls[i].c_str()));
}
void MainWindow::open_com_1(){
    bs.close_com();
    bool isopen = false;
    if(ui->open_com->text()==tr("打开")){
        if(bs.open_com(ui->com_list->currentText().toStdString())){
            ui->open_com->setText(tr("断开"));
            ui->com_list->setDisabled(true);
            ui->refresh_com->setDisabled(true);
            isopen = true;
        }
        else
             bs.close_com();
    }else{
        bs.close_com();
        ui->open_com->setText(tr("打开"));
        ui->com_list->setEnabled(true);
        ui->refresh_com->setEnabled(true);
    }
    if(isopen){
        unsigned char ini_data[]= {0x43,0x42,0x00,0x00,0x01,0x00,0x0A,
                                   0x02,0x00,0x04,0x7B,0x1C,
                                   0x00,0x01,0x00,0x00,0x0A,0x51,0x50,
                                   0x03,0x01,0x05,0x21,0x20,0x51,0x50
                                  };
        for(auto c:ini_data)
            bs.sp<<c;
        bs.set_sys_freq(2460);
        refresh_1();
    }
}
void MainWindow::auto_io_update_1(bool b){
    bs.set_auto_ioupdate(b);
    flashAct->setDisabled(b);
}
void MainWindow::io_update_1(){
    bs.get_cur_state().io_update();
}
void MainWindow::reset_1(){
    bs.rest();
}
void MainWindow::cal_DAC_1(){
    bs.cal_dac();
}
void MainWindow::cal_PLL_1(){
    bs.cal_pll();
}
void MainWindow::change_sys_freq_1(QString Qs_freq){
    bs.set_sys_freq(Qs_freq.toDouble());
    systemClockValLabel->setText(QString::number(bs.get_sys_freq(),'g',10));
}
void MainWindow::change_multiplier_1(QString Qs_mul){

}

void MainWindow::ini_1(){
    connect(ui->refresh_com,SIGNAL(clicked(bool)),this,SLOT(refresh_com_list_1()));
    connect(ui->open_com,SIGNAL(clicked(bool)),this,SLOT(open_com_1()));
    connect(ui->osk_enable,SIGNAL(clicked(bool)),this,SLOT(set_osk_1(bool)));
    connect(ui->external_osk_enable,SIGNAL(clicked(bool)),this,SLOT(set_ext_osk_1(bool)));
    connect(ui->external_osk_pin_en,SIGNAL(clicked(bool)),this,SLOT(set_ext_pin_osk_1(bool)));
    connect(newAct,SIGNAL(triggered(bool)),this,SLOT(reset_1()));
    connect(loadAct,SIGNAL(triggered(bool)),this,SLOT(cal_DAC_1()));
    connect(closeAct,SIGNAL(triggered(bool)),this,SLOT(cal_PLL_1()));
    connect(flashAct,SIGNAL(triggered(bool)),this,SLOT(io_update_1()));
    connect(ui->auto_io_update,SIGNAL(clicked(bool)),this,SLOT(auto_io_update_1(bool)));
    connect(clockLineEdit,SIGNAL(textChanged(QString)),this,SLOT(change_sys_freq_1(QString)));
    systemClockValLabel->setStyleSheet("color:blue;font:bold;");
    refresh_1();
}
void MainWindow::refresh_1(){
    refresh_com_list_1();
    ui->osk_enable->setChecked(bs.get_osk_enable());
    ui->external_osk_enable->setChecked(bs.get_external_oskenable());
    ui->external_osk_pin_en->setChecked(bs.get_cur_state().get_osk());
    ui->auto_io_update->setChecked(bs.get_auto_ioupdate());
    flashAct->setDisabled(bs.get_auto_ioupdate());
    clockLineEdit->setText(QString::number(bs.get_sys_freq(),'g',10));
    systemClockValLabel->setText(QString::number(bs.get_sys_freq(),'g',10));
}
