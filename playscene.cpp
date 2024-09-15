#include<QPen>
#include<QPainter>
#include<QColor>
#include<QToolBar>
#include<config.h>
#include<QLabel>
#include<QFont>
#include<game.h>
#include<QIcon>
#include<playscene.h>

PlayScene::PlayScene(QWidget *parent)
    : QMainWindow{parent}
{
    /*
     *窗口参数初始化
     */
    this->setFixedSize(Play_Width,Play_Height);
    this->setWindowTitle("异形工厂");
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(23);
    setupButtons();
    setMouseTracking(true);
    /*
     *游戏窗口子界面建立
     */
    storeScene=new StoreScene;
    helpScene=new HelpScene;
    /*
     *音乐相关
     */
    QProcess *musicProcess = new QProcess(this);
    QString program = "cmd";
    QStringList arguments;
    QString musicFile = "D:/project_qt/final_project/music/game.mp3";
    arguments << "/c" << "start" << "/min" << "wmplayer" << musicFile;

    /*
     *游戏界面按钮槽函数
     */


    connect(StoreBtn,&QPushButton::clicked,[=](){//进入到商店界面
        this->hide();//主界面隐藏
        storeScene->show();
    });
    connect(HelpBtn,&QPushButton::clicked,[=](){//进入到帮助界面
        this->hide();
        helpScene->show();
    });
    connect(GameBackBtn,&QPushButton::clicked,[=](){//返回选择界面
        emit gameBack();
    });
    connect(SoundOnBtn, &QPushButton::clicked, this, [=]() {
            musicProcess->start(program, arguments);
    });
    connect(A_Btn,&QPushButton::clicked, this, [=]()
            { this->SelectName="A"; });
    connect(B_Btn,&QPushButton::clicked, this, [=]()
            { this->SelectName="B"; });
    connect(C_Btn,&QPushButton::clicked, this, [=]()
            { this->SelectName="C"; });
    connect(D_Btn,&QPushButton::clicked, this, [=]()
            { this->SelectName="D"; });
    connect(E_Btn,&QPushButton::clicked, this, [=]()
            { this->SelectName="E"; });
    connect(F_Btn,&QPushButton::clicked, this, [=]()
            { this->SelectName="F"; });
    /*
     * 开始刷新游戏
     */
    BeginUpdate();
}


//todo
void PlayScene::setupButtons(){
    StoreBtn = new MyPushButton;
    StoreBtn->setParent(this);
    StoreBtn->setFixedSize(Button_Size, Button_Size);
    StoreBtn->setStyleSheet("QPushButton{image: url(:/res/store_button.png)}");
     StoreBtn->move(50,820);


    SaveBtn = new MyPushButton;
    SaveBtn->setParent(this);
    SaveBtn->setFixedSize(Button_Size/2, Button_Size/2);
    SaveBtn->setStyleSheet("QPushButton{image: url(:/res/save.png)}");
    SaveBtn->move(50,880);

    LoadBtn = new MyPushButton;
    LoadBtn->setParent(this);
    LoadBtn->setFixedSize(Button_Size/2, Button_Size/2);
    LoadBtn->setStyleSheet("QPushButton{image: url(:/res/load.png)}");
    LoadBtn->move(50,940);

    GameBackBtn = new MyPushButton;
    GameBackBtn->setParent(this);
    GameBackBtn->setFixedSize(Button_Size/2, Button_Size/2);
    GameBackBtn->setStyleSheet("QPushButton{image: url(:/res/game_back.png)}");
    GameBackBtn->move(50,1000);

    HelpBtn = new MyPushButton;
    HelpBtn->setParent(this);
    HelpBtn->setFixedSize(Button_Size/2, Button_Size/2);
    HelpBtn->setStyleSheet("QPushButton{image: url(:/res/help.png)}");
    HelpBtn->move(50,1060);

    SoundOnBtn = new MyPushButton;
    SoundOnBtn->setParent(this);
    SoundOnBtn->setFixedSize(Button_Size/2, Button_Size/2);
    SoundOnBtn->setStyleSheet("QPushButton{image: url(:/res/sound_on.png)}");
    SoundOnBtn->move(50,1120);

    A_Btn = new MyPushButton;
    A_Btn->setParent(this);
    A_Btn->setFixedSize(50, 100);
    A_Btn->setStyleSheet("QPushButton{image: url(:/res/A_0.png)}");
    A_Btn->move(50,50);

    B_Btn = new MyPushButton;
    B_Btn->setParent(this);
    B_Btn->setFixedSize(50, 100);
    B_Btn->setStyleSheet("QPushButton{image: url(:/res/B_0.png)}");
    B_Btn->move(50,150);

    C_Btn = new MyPushButton;
    C_Btn->setParent(this);
    C_Btn->setFixedSize(50,100);
    C_Btn->setStyleSheet("QPushButton{image: url(:/res/C_0.png)}");
    C_Btn->move(50,250);

    D_Btn = new MyPushButton;
    D_Btn->setParent(this);
    D_Btn->setFixedSize(50,100);
    D_Btn->setStyleSheet("QPushButton{image: url(:/res/D_0.png)}");
    D_Btn->move(50,350);


    E_Btn = new MyPushButton;
    E_Btn->setParent(this);
    E_Btn->setFixedSize(50,100);
    E_Btn->setStyleSheet("QPushButton{image: url(:/res/E_0.png)}");
    E_Btn->move(50,450);

    F_Btn = new MyPushButton;
    F_Btn->setParent(this);
    F_Btn->setFixedSize(50,100);
    F_Btn->setStyleSheet("QPushButton{image: url(:/res/F_0.png)}");
    F_Btn->move(50,550);

}

void PlayScene::setupRoles(){
    for(auto it = game.OurRoles.begin(); it != game.OurRoles.end();){
        auto role=*it;
            QString path=":/res/_.png";
        path.insert(6,role->name);
            int ind=path.indexOf('.');
        if(role->health<=0)role->state=4;
        path.insert(ind,QString::number(role->state));
            QPainter painter1(this);
            QPainter painterline1(this);
            QPainter painterline2(this);
            painterline1.setPen(QPen(Qt::red, 2));
            painterline1.setPen(QPen(Qt::blue, 2));
            QPoint start1=QPoint(role->posi*Cell_Size+Left_Width-40,role->posj*Cell_Size+Up_Height+5);
            QPoint end1=QPoint(role->posi*Cell_Size+Left_Width-40+0.8*role->health,role->posj*Cell_Size+Up_Height+5);
             QPoint start2=QPoint(role->posi*Cell_Size+Left_Width-40,role->posj*Cell_Size+Up_Height+10);
            QPoint end2=QPoint(role->posi*Cell_Size+Left_Width-40+0.8*role->health,role->posj*Cell_Size+Up_Height+10);
            painterline1.drawLine(start1,end1);
            painterline2.drawLine(start1,end2);
        if(role->state==4){
            painter1.drawPixmap(role->posi *Cell_Size, role->posj*Cell_Size, Cell_Size-20, Cell_Size-20, path);
            auto temp=role;
            it = game.OurRoles.erase(it);
            delete temp;
            }
        if(role->be_attacking){
                QPixmap pixmap(path);
            painter1.drawPixmap(role->posi *Cell_Size+Left_Width, role->posj*Cell_Size+Up_Height, Cell_Size-20, Cell_Size-20, path);
                    QPixmap whiteMask(pixmap.size());
                    whiteMask.fill(Qt::white);

                    painter1.setCompositionMode(QPainter::CompositionMode_Plus);
                    painter1.drawPixmap(role->posi *Cell_Size, role->posj*Cell_Size, whiteMask);
            }
        else painter1.drawPixmap(role->posi *Cell_Size, role->posj*Cell_Size, Cell_Size-20, Cell_Size-20, path);


            for(auto bullet:role->Bullets){
                QString name=bullet->name;
                QString path_item=":/res/_bullet.png";
                        path_item.insert(6,name);
                painter1.drawPixmap(bullet->posx,bullet->posy,Cell_Size-20, Cell_Size-20, path_item);
                    }

            it++;
      }
}

void PlayScene::setupCells(){
    QPen pen;
    pen.setColor(QColor(200,200,200));
    QPainter painter(this);
    painter.setPen(pen);
    for (int y = 100; y <=Play_Height-Prop_Widget_Height; y += Cell_Size)
    {
       painter.drawLine(0, y, Play_Width, y);
    }
    for (int x =30; x <Play_Width; x +=Cell_Size)
    {painter.drawLine(x, 0, x, Play_Height-Prop_Widget_Height);
    }
}


void PlayScene::setupBlueRole(){
    if(SelectName!=nullptr){
        QString path=":/res/_blue.png";
        path.insert(6,SelectName);
        int ind=path.indexOf('.');
        path.insert(ind,SelectName);
        QPixmap pixmap(path);
        QPainter painter2(this);
        painter2.drawPixmap(SelectPos.i,SelectPos.j,Selectw, Selecth,pixmap);
        }
    else return;
}


void PlayScene::setupText(){
    QPainter painter4(this);
    painter4.setFont(QFont("宋体",25, QFont::Bold));
    QString text1="Score:";
    QString text2="Money:";
    painter4.drawText(1000, 870, text2+QString::number(game.money));
    painter4.drawText(30,this->height()-20,QString("Level")+QString::number(game.round));
}


void PlayScene::paintEvent(QPaintEvent *)
{

    setupCells();
    setupBlueRole();
    setupRoles();
    setupText();
    connect(helpScene,&HelpScene::HelpSceneback,this,[=](){
        helpScene->hide();
        this->show();
    });
    connect(storeScene,&StoreScene::StoreSceneback_money,this,[=](){
        disconnect(storeScene, &StoreScene::StoreSceneback_money, this, nullptr);
        this->show();
        if(game.money>=20){
            game.money-=20;;
            QMessageBox::information(this, "Store", "Buy successfully!");
        }
        else QMessageBox::information(this, "Store", "No enough money");
    });
    connect(storeScene,&StoreScene::StoreSceneback_belt,this,[=](){
        disconnect(storeScene, &StoreScene::StoreSceneback_belt, this, nullptr);
        this->show();
        if(game.money>=30){
            game.money-=30;
            QMessageBox::information(this, "Store", "Buy successfully!");
        }
        else QMessageBox::information(this, "Store", "No enough money");
    });
    connect(storeScene,&StoreScene::StoreSceneback_cutter,this,[=](){
        disconnect(storeScene, &StoreScene::StoreSceneback_cutter, this, nullptr);
        this->show();
        if(game.money>=40){
            QMessageBox::information(this, "Store", "Buy successfully!");
        }
        else QMessageBox::information(this, "Store", "No enough money");
    });


}
void PlayScene::mousePressEvent(QMouseEvent *event)
{

    //把鼠标点击的监听放在playscene
    int click_x = event->pos().x();
    int click_y = event->pos().y();
    if (event->button() == Qt::LeftButton)
    {
        if (SelectName!=nullptr&&game.IsValid(gridvec(SelectPos.i,SelectPos.j)))
        {//如果有待放置的建筑物的名字
            if(SelectName=="A"&&game.money>=8){
                SelectRole=new Role_A(SelectPos.i,SelectPos.j);
                game.money-=8;
            }
            if(SelectName=="B"&&game.money>=30){
                game.money-=30;
                SelectRole=new role_B(SelectPos.i,SelectPos.j);
            }

            if(SelectName=="C"&&game.money>=12){
                game.money-=12;
                SelectRole=new role_C(SelectPos.i,SelectPos.j);
            }
            if(SelectName=="D"&&game.money>=24){
                game.money-=24;
                SelectRole=new role_D(SelectPos.i,SelectPos.j);
            }
            if(SelectName=="E"&&game.money>=25){
                game.money-=25;
                SelectRole=new role_E(SelectPos.i,SelectPos.j);
            }
            if(SelectName=="F"&&game.money>=13){
                game.money-=13;
                SelectRole=new role_F(SelectPos.i,SelectPos.j);
            }

            if(SelectRole){
                game.OurRoles.push_back(SelectRole);
                SelectRole=NULL;
            }
        }
}
    else if (event->button() == Qt::RightButton)
    {
        SelectName.clear();
        game.RemoveRole(GridVec((click_x-Left_Width)/Cell_Size,(click_y-Up_Height)/Cell_Size));
        update();
    }
}
void PlayScene::mouseDoubleClickEvent (QMouseEvent *event) {
    int click_x = event->pos().x();
    int click_y = event->pos().y();
    if (event->button() == Qt::LeftButton) {
        MyRole*role=game.GetRole(GridVec((click_x-Left_Width)/Cell_Size,(click_y-Up_Height)/Cell_Size));
        if(!role->timer_skillcd.isActive()){
            role->state=3;
        }
}
}
void PlayScene::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
    int x = event->pos().x();      // 鼠标点击的屏幕位置的横坐标
    int y = event->pos().y();      // 鼠标点击的屏幕位置的纵坐标
    if (SelectName!=nullptr)
    {
        SelectPos.i=x;
        SelectPos.j=y;
    }
}
void PlayScene::EnemyCome(){
    if(game.enemy_timer.remainingTime()<75000&&game.batch==3){
        game.batch++;
        for(int i=0;i<10;i++){
            MyRole*SelectEnemy=NULL;
            if(game.EnemyList[3][i]=='G'){
                SelectEnemy=new Role_G(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='H'){
                SelectEnemy=new Role_H(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='I'){
                SelectEnemy=new Role_I(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='J'){
                SelectEnemy=new Role_J(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='K'){
                SelectEnemy=new Role_K(QRandomGenerator::global()->bounded(6));
            }
            game.EnemyRoles.append(SelectEnemy);
            }

        }
    else if(game.enemy_timer.remainingTime()<150000&&game.batch==2){
        game.batch++;
        for(int i=0;i<10;i++){
            MyRole*SelectEnemy=NULL;
            if(game.EnemyList[2][i]=='G'){
                SelectEnemy=new Role_G(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[2][i]=='H'){
                SelectEnemy=new Role_H(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[2][i]=='I'){
                SelectEnemy=new Role_I(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[2][i]=='J'){
                SelectEnemy=new Role_J(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[2][i]=='K'){
                SelectEnemy=new Role_K(QRandomGenerator::global()->bounded(6));
            }
            game.EnemyRoles.append(SelectEnemy);
        }
    }
        else if(game.enemy_timer.remainingTime()<225000&&game.batch==1){
            for(int i=0;i<10;i++){
                MyRole*SelectEnemy=NULL;
                if(game.EnemyList[1][i]=='G'){
                    SelectEnemy=new Role_G(QRandomGenerator::global()->bounded(6));
                }
                else if(game.EnemyList[1][i]=='H'){
                    SelectEnemy=new Role_H(QRandomGenerator::global()->bounded(6));
                }
                else if(game.EnemyList[1][i]=='I'){
                    SelectEnemy=new Role_I(QRandomGenerator::global()->bounded(6));
                }
                else if(game.EnemyList[1][i]=='J'){
                    SelectEnemy=new Role_J(QRandomGenerator::global()->bounded(6));
                }
                else if(game.EnemyList[1][i]=='K'){
                    SelectEnemy=new Role_K(QRandomGenerator::global()->bounded(6));
                }
                game.EnemyRoles.append(SelectEnemy);
            }
        }
        else if(game.enemy_timer.remainingTime()<290000&&game.batch==0){
        game.batch++;
        for(int i=0;i<10;i++){
            MyRole*SelectEnemy=NULL;
            if(game.EnemyList[3][i]=='G'){
                SelectEnemy=new Role_G(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='H'){
                SelectEnemy=new Role_H(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='I'){
                SelectEnemy=new Role_I(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='J'){
                SelectEnemy=new Role_J(QRandomGenerator::global()->bounded(6));
            }
            else if(game.EnemyList[3][i]=='K'){
                SelectEnemy=new Role_K(QRandomGenerator::global()->bounded(6));
            }
            game.EnemyRoles.append(SelectEnemy);
        }
    }
    }

void PlayScene::BeginUpdate()
{//工厂开始动
    timer.start(50);
    // 监听定时器
    connect(&timer, &QTimer::timeout, this, [=]()
{
        money_timer++;
        if(money_timer==20){
            money_timer=0;
            game.money++;
        }
        //这里是每隔一段时间就重绘地图和更新地图中传送带的运行
                //重新绘制图片
         update();
             for(auto role:game.OurRoles)
                 role->UpdateState(game);
             for(auto role:game.EnemyRoles)
                 role->UpdateState(game);
             EnemyCome();
    });
}

void PlayScene::saveGame() {
    QFile file("savegame.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out <<game.round<< "\n";
        out << game.OurRoles.size();
        for (const MyRole *role :game.OurRoles) {
            out<<role->name<<"\n";
            out<<role->posi<<"\n";
            out<<role->posj<<"\n";
        }
        for (const MyRole *role :game.EnemyRoles) {
            out<<role->name<<"\n";
            out<<role->posi<<"\n";
            out<<role->posj<<"\n";
        }
        file.close();
        QMessageBox::information(this, "Save Game", "Game saved successfully!");
    } else {
        QMessageBox::warning(this, "Save Game", "Failed to save game!");
    }
}
void PlayScene::loadGame() {
    return;
}

