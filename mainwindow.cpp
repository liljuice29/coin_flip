#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSoundEffect>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //配置主场景

    //配置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始音效
    QSoundEffect * startsound=new QSoundEffect(this);
    startsound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //开始按钮
    mypushbutton* startbtn=new mypushbutton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    //实例化关卡场景
    choosescene * chs =new choosescene;

    //监听选择关卡的返回按钮信号
    connect(chs,&choosescene::choosesceneback,[=](){
        this->setGeometry(chs->geometry());
        chs->hide();
        this->show();
    });

    connect(startbtn,&mypushbutton::clicked,[=](){
        //播放开始音效
        startsound->play();

        //做弹跳特效
        startbtn->zoom1();
        startbtn->zoom2();

        //延时进入到选择关卡场景
        QTimer::singleShot(400,this,[=](){
            chs->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡
            chs->show();
        });

    });
}

 void MainWindow::paintEvent(QPaintEvent*)
{

     QPainter painter(this);
    QPixmap pix;
     //画背景图
     pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    //对图标进行缩放
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
