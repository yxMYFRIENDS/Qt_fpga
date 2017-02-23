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


    ~MainWindow();
public slots:
    void CloseAction();

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
    QAction* flash1Act;
    //工具栏按钮
    QLabel* clockLabel;
    QLineEdit* clockLineEdit;
    QLabel* multiplierLabel;
    QLineEdit* multiplierLineEdit;
    QLabel* systemClockLabel;
    QLabel* systemClockValLabel;



};

#endif // MAINWINDOW_H
