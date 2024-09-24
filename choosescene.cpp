#include "choosescene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QSoundEffect>
choosescene::choosescene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("选择关卡场景");
    //创建菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* startMenu=bar->addMenu("开始");
    QAction* quitaction=startMenu->addAction("退出");
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });

    QSoundEffect * choosesound=new QSoundEffect(this);
    choosesound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    QSoundEffect * backsound=new QSoundEffect(this);
    backsound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //返回按钮
    mypushbutton* backbtn=new mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
    connect(backbtn,&mypushbutton::clicked,[=](){
        backsound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->choosesceneback();
        });

    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)//通过一个for循环写出一个矩阵,对列取模对行取整
    {
        mypushbutton* menubtn=new mypushbutton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menubtn,&mypushbutton::clicked,[=](){
            choosesound->play();
            //进入游戏场景
            this->hide();
            play=new playscene(i+1);
            play->show();

            play->setGeometry(this->geometry());

            connect(play,&playscene::choosesceneback,[=](){
                this->setGeometry(this->geometry());
                this->show();
                delete play;
                play=nullptr;
            });

        });


        //创建按钮关卡数字
        QLabel* label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        //设置数字水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标穿透label
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void choosescene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //画背景图
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/res/Title.png");
    //对图标进行缩放
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}
