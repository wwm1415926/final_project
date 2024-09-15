#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QPropertyAnimation>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normal,QString press="");
    /*
     *两种外观的图片路径
     */
    QString normalPath;
    QString pressPath;
    /*
     *动画效果
     */
    void zoom1();
    void zoom2();
    /*
     *按钮名称
     */
    QString name;

signals:

};

#endif // MYPUSHBUTTON_H
