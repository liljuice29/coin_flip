#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include"playscene.h"
class choosescene : public QMainWindow
{
    Q_OBJECT
public:
    explicit choosescene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent*);

    //游戏场景对象指针
    playscene* play=nullptr;

signals:
    //写一个自定义信号，告诉主场景点击了返回
    void choosesceneback();
};

#endif // CHOOSESCENE_H
