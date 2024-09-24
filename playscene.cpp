#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSoundEffect>
// playscene::playscene(QWidget *parent)
//     : QMainWindow{parent}
// {}

playscene::playscene(int levelnum)
{
    levelindex=levelnum;

    //初始化游戏场景

    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");
    //创建菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* startMenu=bar->addMenu("开始");
    QAction* quitaction=startMenu->addAction("退出");
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });
    QSoundEffect * backsound=new QSoundEffect(this);
    backsound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    QSoundEffect * flipsound=new QSoundEffect(this);
    flipsound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    QSoundEffect * winsound=new QSoundEffect(this);
    winsound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));

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

//显示当前关卡数
    QLabel* label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1=QString("level: %1").arg(this->levelindex);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(20,this->height()-50,120,50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gamearray[i][j]=config.mData[this->levelindex][i][j];

        }
    }

    //胜利图标显示
    QLabel* winlabel=new QLabel;
    QPixmap tmppix;
    tmppix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,tmppix.width(),tmppix.height());
    winlabel->setPixmap(tmppix);
    winlabel->setParent(this);
    winlabel->move(this->width()*0.5-tmppix.width()*0.5,-tmppix.height());


    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel * label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gamearray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            mycoin* coin=new mycoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币属性赋值
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->gamearray[i][j];

            //将金币放入金币的二维数组里，以便后期维护
            coinbtn[i][j]=coin;

            //点击金币 进行翻转
            connect(coin,&mycoin::clicked,[=](){
                flipsound->play();
                coin->changeflag();
                this->gamearray[i][j]=this->gamearray[i][j]==0?1:0;

                //延时翻转周围金币
                QTimer::singleShot(300,this,[=](){
                    if(coin->posx+1<=3)//右侧硬币翻转
                    {
                        coinbtn[coin->posx+1][coin->posy]->changeflag();
                        this->gamearray[coin->posx+1][coin->posy]=this->gamearray[coin->posx+1][coin->posy]==0?1:0;
                    }

                    if(coin->posx-1>=0)//右侧硬币翻转
                    {
                        coinbtn[coin->posx-1][coin->posy]->changeflag();
                        this->gamearray[coin->posx-1][coin->posy]=this->gamearray[coin->posx-1][coin->posy]==0?1:0;
                    }

                    if(coin->posy+1<=3)//上侧硬币翻转
                    {
                        coinbtn[coin->posx][coin->posy+1]->changeflag();
                        this->gamearray[coin->posx][coin->posy+1]=this->gamearray[coin->posx][coin->posy+1]==0?1:0;
                    }

                    if(coin->posy-1>=0)//下侧硬币翻转
                    {
                        coinbtn[coin->posx][coin->posy-1]->changeflag();
                        this->gamearray[coin->posx][coin->posy-1]=this->gamearray[coin->posx][coin->posy-1]==0?1:0;
                    }

                    //判断是否胜利
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)
                            {
                                iswin=false;
                                break;
                            }
                        }
                    }
                    if(iswin)
                    {
                        winsound->play();
                        //将所有按钮胜利标志改为true
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinbtn[i][j]->iswin=true;
                            }
                        }
                        //将胜利图片向下移动
                        QPropertyAnimation* animation=new QPropertyAnimation(winlabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        //设置结束位置
                         animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                        //设置曲线
                         animation->setEasingCurve(QEasingCurve::OutBounce);
                         //执行动画
                         animation->start();
                    }


                });






            });

        }
    }



}

void playscene::paintEvent(QPaintEvent*)
{
  //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}







