#ifndef STORESCENE_H
#define STORESCENE_H

#include <QMainWindow>
#include<mypushbutton.h>
#include<QPainter>
#include<game.h>
class StoreScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit StoreScene(QWidget *parent = nullptr);
    /*
     *绘制商店界面
     */
    void paintEvent(QPaintEvent *);
    void setupChoose();
    MyPushButton*MoneyBtn,*CutterBtn,*BeltBtn;
signals:
    /*
     *商店界面回传给游戏界面的信号
     */
    void StoreSceneback_belt();
    void StoreSceneback_cutter();
    void StoreSceneback_money();
};

#endif // STORESCENE_H
