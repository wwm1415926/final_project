#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <QMainWindow>
#include<myRole.h>
#include<QLabel>
#include<QPixmap>
#include<QImage>
#include<game.h>
#include<QPushButton>
#include<mypushbutton.h>
#include<QPainter>
#include<QMouseEvent>
#include<role_C.h>
#include<role_B.h>
#include<role_A.h>
#include<role_D.h>
#include<role_E.h>
#include<role_F.h>
#include<role_G.h>
#include<role_H.h>
#include<role_I.h>
#include<role_J.h>
#include<role_K.h>
#include<storescene.h>
#include<helpscene.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDataStream>
#include <QProcess>
#include<QRandomGenerator>
#include<QMap>
#include <QPolygon>
#include<QLinearGradient>
class Game;
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    /*
     *系列初始化地图画面的操作
     */

    void setupButtons();//初始化游戏界面按钮
    void setupRoles();//建立玩家放置建筑
    void setupBlueRole();//建立蓝色覆盖层
    void setupCells();//建立方格
    void setupItems();//建立建筑物上的物体
    void setupText();//建立文本框
public:
    Game game;
    /*
     *游戏界面上可点击按钮
     */
    MyPushButton*HelpBtn,*StoreBtn,*SaveBtn,
        *LoadBtn,*GameBackBtn,*SoundOnBtn,*A_Btn,*B_Btn,*C_Btn,*D_Btn,*E_Btn,*F_Btn;

    //todo 存放所有角色，并摆放在画面上方
    QList<MyPushButton*>RoleBtns;


    /*
     *玩家选中和鼠标移动
     */
    MyRole*SelectRole;
    QString SelectName; // 当前选中的名称
    GridVec SelectPos;//鼠标位置
    int Selecth,Selectw;
    int Select_X,Select_Y;//建筑物固定的方格和坐标
    QTimer enemy_timer;

    /*
     *游玩界面的成员对象界面
     */
    StoreScene* storeScene;//商店界面
    HelpScene* helpScene;//帮助界面

    /*
     *画面绘制与键鼠响应函数
     */
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    using QMainWindow::mousePressEvent;
    void mousePressEvent(QMouseEvent *event)override;
    void EnemyCome();

    /*
     * 用于控制游戏画面的刷新
     */
    QTimer timer;
    void BeginUpdate();
    int money_timer=0;

signals:
    /*
     *回传选择界面的信号，包括玩家主动返回及游戏结束信号
     */
    void gameBack();
    void First_success();
    void Second_success();
    void First_failure();
    void Second_failure();
private slots:

    /*
     *游戏存档与读档函数
     */
    void saveGame();
    void loadGame();

};


#endif // PLAYSCENE_H

