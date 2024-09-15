#include "choosescene.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<mypushbutton.h>
#include<QTimer>
ChooseScene::ChooseScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(800,600);
    this->setWindowTitle("选择关卡");
    second_game=false;
    QPushButton *backBtn=new QPushButton("Back",this);
    backBtn->move(650,550);
    MyPushButton *startBtn1=new MyPushButton;
    startBtn1->setParent(this);
    startBtn1->setFixedSize(Button_Size, Button_Size);
    startBtn1->setStyleSheet("QPushButton{image: url(:/res/game1.png)}");
    startBtn1->move(200,300);
    MyPushButton *startBtn2=new MyPushButton;
    startBtn2->setParent(this);
    startBtn2->setFixedSize(Button_Size, Button_Size);
    startBtn2->setStyleSheet("QPushButton{image: url(:/res/game2.png)}");
    startBtn2->move(400,300);
    playScene=new PlayScene;
    playScene->game.money=0;
    connect(startBtn1,&QPushButton::clicked,[=](){//进入到游戏界面
        //特效
        startBtn1->zoom1();
        startBtn1->zoom2();

        for(int i=0;i<24;i++){
            for(int j=0;j<16;j++){
                playScene->game.RemoveBuilding(GridVec(i,j));
                playScene->game.GameMap[i][j]="";
            }
        }
        playScene->game.FirstGame();
        //进入游戏界面
        QTimer::singleShot(500,this,[=](){
            this->hide();
            playScene->show();
        });

    });
    connect(startBtn2,&QPushButton::clicked,[=](){
        if(this->second_game==false){
            QMessageBox::information(this, "NAN", "关卡尚未解锁！");
            return;
        }
        if(this->second_game==true){
        //特效
        startBtn2->zoom1();
        startBtn2->zoom2();
        for(int i=0;i<24;i++){
            for(int j=0;j<16;j++){
                playScene->game.RemoveBuilding(GridVec(i,j));
                playScene->game.GameMap[i][j]="";
            }
        }
        playScene->game.SecondGame();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            playScene->show();
        });
        }
    });
    connect(backBtn,&QPushButton::clicked,[=](){
        emit chooseSceneBack();
    });
}
void ChooseScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QImage background2(":/res/choose_background.png");
    painter.drawImage(QRect(0, 0, 800, 600), background2);

    QImage background1(":/res/choosescene.png");
    painter.drawImage(QRect(0, 0, 800, 100),background1);
    connect(playScene,&PlayScene::gameBack,this,[=](){
        playScene->hide();
        this->show();
    });

    connect(playScene,&PlayScene::First_success,this,[=](){
        disconnect(playScene, &PlayScene::First_success, this, nullptr);
        second_game=true;
        playScene->hide();
        this->show();
    });
    connect(playScene,&PlayScene::Second_success,this,[=](){
        disconnect(playScene, &PlayScene::Second_success, this, nullptr);
        playScene->hide();
        this->show();
    });

}

