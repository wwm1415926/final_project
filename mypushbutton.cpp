#include "mypushbutton.h"
#
MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{


}
MyPushButton::MyPushButton(QString normal,QString press){
    this->normalPath=normal;
    this->pressPath=press;
    QPixmap pix;
    bool ret=pix.load(normal);
    if(!ret){
    qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    //不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1(){
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2(){
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
