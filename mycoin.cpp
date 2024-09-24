#include "mycoin.h"

mycoin::mycoin(QString btnimg)
{
    QPixmap pix;
    pix.load(btnimg);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //监听正面翻反面的信号，并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=1;
            isanimation=false;
            timer1->stop();
        }

    });

    //监听反面翻正面的信号，并且反转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->max=8;
            isanimation=false;
            timer2->stop();
        }

    });
}

 void mycoin::mousePressEvent(QMouseEvent* e)
{
     if(this->isanimation||this->iswin)
    {
        return ;
     }
     else
     {
         QPushButton::mousePressEvent(e);
     }

}

//改变正反面标志的方法
void mycoin::changeflag()
{
    if(this->flag)
    {
        timer1->start(30);
        isanimation=true;
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        isanimation=true;
        this->flag=true;
    }
}















