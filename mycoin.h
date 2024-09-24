#ifndef MYCOIN_H
#define MYCOIN_H
#include<QTimer>

#include <QPushButton>

class mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit mycoin(QWidget *parent = nullptr);
    //参数代表传入的是金币路径还是银币路径
    mycoin(QString btnimg);

    //金币属性
    int posx;
    int posy;
    bool flag;

    void changeflag();
    QTimer* timer1;
    QTimer* timer2;
    int min=1;
    int max=8;

    //执行动画标志
    bool isanimation=false;

    //重写按下
    void mousePressEvent(QMouseEvent* e);

    //是否胜利标志
    bool iswin=false;

signals:
};

#endif // MYCOIN_H
