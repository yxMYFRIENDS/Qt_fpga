#include "mainwindow.h"
#include "ui_mainwindow.h"

BaseSet bs;    //界面1
Sweep sweep(bs); //界面2
Profil profil(bs);//界面3
CurrentState& cs = bs.get_cur_state();//界面4

//const QString rsrcPath = ":/images";
const QString rsrcPath = "C:/Users//Administrator//Desktop//Qt_fpga//images";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateActions();
    CreateToolBars();


    ini_1();
    ini_2();
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



    //第二个ToolBar
    clockLabel = new QLabel(tr("External Clock(MHz):"));
    clockLineEdit = new QLineEdit(tr("2500"));
    multiplierLabel  = new QLabel(tr("Multiplier:"));
    multiplierLineEdit  = new QLineEdit(tr("0"));
    multiplierLineEdit->setEnabled(false);
    systemClockLabel = new QLabel(tr("System Clock (MHz): "));
    systemClockValLabel = new QLabel(tr("2500"));

}
void MainWindow::CreateToolBars()
{
    ui->mainToolBar->addAction(newAct);
    ui->mainToolBar->addAction(loadAct);
    ui->mainToolBar->addAction(closeAct);
    ui->mainToolBar->addAction(flashAct);

    parameterToolBar = addToolBar(tr("参数"));
    parameterToolBar->addWidget(clockLabel);
    parameterToolBar->addWidget(clockLineEdit);
    parameterToolBar->addWidget(multiplierLabel);
    parameterToolBar->addWidget(multiplierLineEdit);
    parameterToolBar->addWidget(systemClockLabel);
    parameterToolBar->addWidget(systemClockValLabel);

}

