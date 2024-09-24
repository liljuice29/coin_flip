#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"choosescene.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //重写paintevent事件，画背景图
    void paintEvent(QPaintEvent*);

    //初始化关卡场景


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
