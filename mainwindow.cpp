#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "base_set.h"
#include "Profil.h"
#include "Sweep.h"

BaseSet bs;    //界面1
Sweep sweep(bs); //界面2
Profil profil(bs);//界面3
CurrentState& cs = bs.get_cur_state();//界面4

//const QString rsrcPath = ":/images";
const QString rsrcPath = "C:/Users//TT//Desktop//Qt_fpga//images";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateActions();
    CreateToolBars();
    ManageTableWidget();
    //测试WriteData
    Data d(tr("0,1,0,0"),tr("192.168.1.1"));
    WriteData(3,d);
    Data d1(tr("0,1,1,0"),tr("192.168.1.1"));
    WriteData(3,d1);

    // 复选框环节

    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(updateMicroFocus()));
    connect(ui->checkBox_2,SIGNAL(clicked(bool)),this,SLOT(updateMicroFocus()));
    connect(ui->checkBox_3,SIGNAL(clicked(bool)),this,SLOT(updateMicroFocus()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: CloseAction()
{
    QMessageBox::about(this,"关闭","执行关闭功能");
}


void MainWindow:: CreateActions()
{
    //先建立五个功能功能1
    newAct = new QAction(QIcon(rsrcPath + "/protect.png"), tr(" 功能1(&N)"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setToolTip("功能1");                   //设置工具栏按钮的提示文本
    newAct->setStatusTip(tr("功能11"));     //设置状态栏提示文本

    //创建loadACT
    loadAct = new QAction(QIcon(rsrcPath + "/load.png"),tr("加载功能"),this);
    loadAct->setToolTip("加载");
    loadAct->setStatusTip(tr("加载"));
    loadAct->setIconText(tr("加载"));


    //创建关闭图标
    closeAct = new QAction(QIcon(rsrcPath + "/close.png"),tr("关闭功能"),this);
    closeAct->setStatusTip(tr("关闭"));
    closeAct->setToolTip(tr("关闭功能"));
    //创建闪电图标
    flashAct = new QAction(QIcon(rsrcPath + "/flash.png"),tr("功能2"),this);
    flashAct->setToolTip(tr("功能2"));
    flashAct->setStatusTip(tr("功能2"));
    //创建闪电1图标
    flash1Act = new QAction(QIcon(rsrcPath + "/flash1.png"),tr("功能3"),this);
    flash1Act->setToolTip(tr("功能3"));
    flash1Act->setStatusTip(tr("功能3"));


    //第二个ToolBar
    clockLabel = new QLabel(tr("External Clock(MHz):"));
    clockLineEdit = new QLineEdit(tr("2500"));
    clockLineEdit->setEnabled(false);
    multiplierLabel  = new QLabel(tr("Multiplier:"));
    multiplierLineEdit  = new QLineEdit(tr("50"));
    systemClockLabel = new QLabel(tr("System Clock (MHz):"));
    systemClockValLabel = new QLabel(tr("2500"));

}
void MainWindow::CreateToolBars()
{
    debugToolBar = addToolBar(tr("文件"));
    debugToolBar->addAction(newAct);
    debugToolBar->addAction(loadAct);
    debugToolBar->addAction(closeAct);
    debugToolBar->addAction(flashAct);
    debugToolBar->addAction(flash1Act);

    parameterToolBar = addToolBar(tr("参数"));
    parameterToolBar->addWidget(clockLabel);
    parameterToolBar->addWidget(clockLineEdit);
    parameterToolBar->addWidget(multiplierLabel);
    parameterToolBar->addWidget(multiplierLineEdit);
    parameterToolBar->addWidget(systemClockLabel);
    parameterToolBar->addWidget(systemClockValLabel);

}

//管理TableWidget窗口
void MainWindow:: ManageTableWidget()
{
    //先学习QTableWidget使用方法
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("Name")<<tr("Address")<<("Data"));
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Name"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("Address"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("Data"));
    ui->tableWidget->setColumnWidth(0,270);
    ui->tableWidget->setColumnWidth(1,70);
    ui->tableWidget->setColumnWidth(2,330);
    //设置第一列的值
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Control Function Register 1"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Control Function Register 2"));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem("Control Function Register 3"));
    ui->tableWidget->setItem(4,0,new QTableWidgetItem("Control Function Register 4"));
    ui->tableWidget->setItem(5,0,new QTableWidgetItem("Linear Sweep Parameter Word 0"));
    ui->tableWidget->setItem(6,0,new QTableWidgetItem("Linear Sweep Parameter Word 1"));
    ui->tableWidget->setItem(7,0,new QTableWidgetItem("Rising Delta Sweep Parameter Word"));
    ui->tableWidget->setItem(8,0,new QTableWidgetItem("Falling Delta Sweep Parameter Word"));
    ui->tableWidget->setItem(9,0,new QTableWidgetItem("Linear Ramp Sweep Rate Register"));
    ui->tableWidget->setItem(10,0,new QTableWidgetItem("Frequency Skip Register 1"));
    ui->tableWidget->setItem(11,0,new QTableWidgetItem("Frequency Skip Register 2"));
    ui->tableWidget->setItem(12,0,new QTableWidgetItem("Profile 0 FTW Register"));
    ui->tableWidget->setItem(13,0,new QTableWidgetItem("Profile 0 ph/Amp Register"));
    ui->tableWidget->setItem(14,0,new QTableWidgetItem("Profile 1 FTW Register"));
    ui->tableWidget->setItem(15,0,new QTableWidgetItem("Profile 1 ph/Amp Register"));
    ui->tableWidget->setItem(16,0,new QTableWidgetItem("Profile 2 FTW Register"));
    ui->tableWidget->setItem(17,0,new QTableWidgetItem("Profile 2 ph/Amp Register"));
    ui->tableWidget->setItem(18,0,new QTableWidgetItem("Profile 3 FTW Register"));
    ui->tableWidget->setItem(19,0,new QTableWidgetItem("Profile 3 ph/Amp Register"));
    ui->tableWidget->setItem(20,0,new QTableWidgetItem("Profile 4 FTW Register"));
    ui->tableWidget->setItem(21,0,new QTableWidgetItem("Profile 4 ph/Amp Register"));
    ui->tableWidget->setItem(22,0,new QTableWidgetItem("Profile 5 FTW Register"));
    ui->tableWidget->setItem(23,0,new QTableWidgetItem("Profile 5 ph/Amp Register"));
    ui->tableWidget->setItem(24,0,new QTableWidgetItem("Profile 6 FTW Register"));
    ui->tableWidget->setItem(25,0,new QTableWidgetItem("Profile 6 ph/Amp Register"));
    ui->tableWidget->setItem(26,0,new QTableWidgetItem("Profile 7 FTW Register"));
    ui->tableWidget->setItem(27,0,new QTableWidgetItem("Profile 7 ph/Amp Register"));
    ui->tableWidget->setItem(28,0,new QTableWidgetItem("USR 0"));

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //第一行的字体以及背景颜色进行设置
    //QTableWidgetItem* columnHeaderItem0 = ui->tableWidget->horizontalHeaderItem(0);
    //columnHeaderItem0->setFont(QFont(tr("Helvetica")));
    //columnHeaderItem0->setBackground(QBrush(QColor(0,60,10)));
    //columnHeaderItem0->setTextColor(QColor(200,111,30));
}

void MainWindow:: WriteData(int row,Data d)
{
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(d.address));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(d.data));
    return;
}



void MainWindow::on_sendDataBtn_clicked()
{
    QString str = ui->sendDataText->toPlainText();
    qDebug()<<str<<endl;
    bs.get_serial()<<"Hello erfe";
}

//管理复选框的状态
void MainWindow:: updateCheckBoxes()
{
    qDebug()<<"复选框能够使用"<<endl;
}
