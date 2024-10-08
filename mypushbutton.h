#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    //explicit mypushbutton(QWidget *parent = nullptr);

    //构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    mypushbutton(QString normalimg,QString pressimg="");

    //成员属性 保存用户传入的默认显示路径 以及按下后显示的路径
    QString normalimgpath;
    QString pressimgpath;

    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
};

#endif // MYPUSHBUTTON_H
