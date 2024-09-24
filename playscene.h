#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include"mycoin.h"
#include <QMainWindow>

class playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playscene(QWidget *parent = nullptr);
    playscene(int levelnum);

    int levelindex;//记录所选关卡

    //重写paintevent事件
    void paintEvent(QPaintEvent*);

    //二维数组，维护每一个关卡的具体数据
    int gamearray[4][4];

    mycoin* coinbtn[4][4];

    //是否胜利标志
    bool iswin;

signals:
    void choosesceneback();
};

#endif // PLAYSCENE_H
