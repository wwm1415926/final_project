#ifndef HELPSCENE_H
#define HELPSCENE_H
#include <QMainWindow>
#include<mypushbutton.h>
#include<QPainter>
#include<game.h>
class HelpScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelpScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void setupback();
    MyPushButton*backBtn;
signals:
    //写一个信号告诉游戏场景，选择了升级
    void HelpSceneback();
};


#endif // HELPSCENE_H
