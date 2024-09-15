#include "storescene.h"

StoreScene::StoreScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(800,600);
    this->setWindowTitle("升级设备");
    setupChoose();
    connect(MoneyBtn,&QPushButton::clicked,[=](){
        emit this->StoreSceneback_money();
    });
    connect(BeltBtn,&QPushButton::clicked,[=](){
        emit this->StoreSceneback_belt();
    });
    connect(CutterBtn,&QPushButton::clicked,[=](){
        emit this->StoreSceneback_cutter();
    });
}
void StoreScene::setupChoose(){
    MoneyBtn = new MyPushButton;
    MoneyBtn->setParent(this);
    MoneyBtn->setFixedSize(Button_Size, Button_Size);
    MoneyBtn->setStyleSheet("QPushButton{image: url(:/res/money_button.png)}");
    MoneyBtn->move(100,200);

    BeltBtn = new MyPushButton;
    BeltBtn->setParent(this);
    BeltBtn->setFixedSize(Button_Size, Button_Size);
    BeltBtn->setStyleSheet("QPushButton{image: url(:/res/belt_button.png)}");
    BeltBtn->move(300,200);

    CutterBtn = new MyPushButton;
    CutterBtn->setParent(this);
    CutterBtn->setFixedSize(Button_Size, Button_Size);
    CutterBtn->setStyleSheet("QPushButton{image: url(:/res/cutter_button.png)}");
    CutterBtn->move(500,200);
}
void StoreScene::paintEvent(QPaintEvent *){
    QPainter painter1(this);
    painter1.fillRect(rect(), Qt::white);
    QPixmap backgroundImage(":/res/store_background.png");
    painter1.drawPixmap(0, 0, backgroundImage.scaled(size()));
    QPainter painter(this);
    painter.setFont(QFont("宋体",25, QFont::Bold));
    painter.drawText(75,300,"金币数翻倍");
    painter.drawText(75,350,"20金币");
    painter.drawText(300,300,"传送带加速");
    painter.drawText(300,350,"30金币");
    painter.drawText(500,300,"切割机加速");
    painter.drawText(500,350,"40金币");

}
