#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QDebug>
#include <QString>

//状态文件作为一个操作
#include "base_set.h"
#include "Profil.h"
#include "Sweep.h"
#include "my.h"


struct Data
{
    QString address;
    QString data;
    Data(QString add,QString d):address(add),data(d){}
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //创建工具栏
    void CreateToolBars();
    void CreateActions();

    //管理QTableWidget空间函数
    void ManageTableWidget();
    void WriteData(int row,Data d);
    //处理复选框的状态
    void updateCheckBoxes();

    void ini_1();
    void refresh_1();
    void ini_2();
    void refresh_2();

    ~MainWindow();
public slots:
    void CloseAction();

private slots:
    /** jiemian1 **/
    void set_osk_1(bool);
    void set_ext_osk_1(bool);
    void set_ext_pin_osk_1(bool);
    void refresh_com_list_1();
    void open_com_1();
    void reset_1();
    void cal_DAC_1();
    void cal_PLL_1();
    void auto_io_update_1(bool);
    void io_update_1();
    void change_sys_freq_1(QString);
    void change_multiplier_1(QString);

    /** jiemian2 **/
    void set_io_update(bool);
    void set_enable_sweep(bool);
    void set_enable_frequency_jump(bool);
    void set_drctl(bool);
    void set_auto_drctl(bool);
    void set_Dwell_High(bool);
    void set_Dwell_Low(bool);
    void change_value_0(QString);
    void change_value_1(QString);
    void change_value_2(QString);
    void change_value_3(QString);
    void change_value_4(QString);
    void change_value_5(QString);
    void change_value_6(QString);
    void change_value_7(QString);



    void on_set_io_update_clicked();

private:
    Ui::MainWindow *ui;

    //添加工具栏
    QToolBar* debugToolBar;
    QToolBar* parameterToolBar;
    //工具栏按钮
    QAction* newAct;
    QAction* loadAct;
    QAction* closeAct;
    QAction* flashAct;
    //工具栏按钮
    QLabel* clockLabel;
    QLineEdit* clockLineEdit;
    QLabel* multiplierLabel;
    QLineEdit* multiplierLineEdit;
    QLabel* systemClockLabel;
    QLabel* systemClockValLabel;






};

#endif // MAINWINDOW_H
