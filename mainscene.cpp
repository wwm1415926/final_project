#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include <QMouseEvent>
#include<QTimer>
#include<mypushbutton.h>

MainScene::MainScene(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主要场景
    setFixedSize(1200,720);
    setWindowTitle("xx大战xx");
    chooseScene=new ChooseScene;
}

void MainScene::paintEvent(QPaintEvent*){

     QPainter painter(this);
    QPixmap pix;
     pix.load(":/res/main_background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
     //画背景上图标
    pix.load(":res/start.png");
    pix=pix.scaled(pix.width()*0.2,pix.height()*0.2);
    painter.drawPixmap(465,270,pix);

    //监听选择关卡按钮的信号
    connect(chooseScene,&ChooseScene::chooseSceneBack,this,[=](){
        chooseScene->hide();
        this->show();
    });
    connect(ui->startBtn,&QPushButton::clicked,[=](){//进入到选择界面
        this->hide();//主界面隐藏
        chooseScene->show();
    });
}
MainScene::~MainScene()
{
    delete ui;
}
