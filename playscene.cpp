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
    this->setWindowTitle("xx大战xx");
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


    QLabel *label1 = new QLabel(this); // 这里的this是指向你的父控件或窗口的指针
    QPainter painter(this);
    QString path1(":/res/game_cell.png");
    int rows = 6;
    int columns = 12;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
           painter.drawPixmap(i * Cell_Size + Left_Width, j * Cell_Size + Up_Height, Cell_Size, Cell_Size, path1);
        }
    }
    QPixmap pixmap1(":/res/warning.png");
    QLabel *label2 = new QLabel(this); // 这里的this是指向你的父控件或窗口的指针
    label2->setFixedSize(30,720);
    label2->setParent(this);
    label2->setPixmap(pixmap1); // 设置QLabel的pixmap
    label2->move(0, 100); // 如果你需要确保QLabel也在父控件的(0,0)位置
    label2->show();
    QPixmap pixmap2(":/res/game_buttom.png");
    QLabel *label3 = new QLabel(this); // 这里的this是指向你的父控件或窗口的指针
    label3->setFixedSize(1200,20);
    label3->setParent(this);
    label3->setPixmap(pixmap2); // 设置QLabel的pixmap
    label3->move(0,1180); // 如果你需要确保QLabel也在父控件的(0,0)位置
    label3->show();




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
            {
                this->SelectName="A"; });
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
    QPixmap pixmap2(":/res/game_card.png");
    QLabel *label2 = new QLabel(this); // 这里的this是指向你的父控件或窗口的指针
    label2->setFixedSize(1200,100);
    label2->setParent(this);
    label2->setPixmap(pixmap2); // 设置QLabel的pixmap
    label2->move(0, 0); // 如果你需要确保QLabel也在父控件的(0,0)位置
    label2->show();
    StoreBtn = new MyPushButton;
    StoreBtn->setParent(this);
    StoreBtn->setFixedSize(Button_Size/2, Button_Size/2);
    StoreBtn->setStyleSheet("QPushButton{image: url(:/res/store_button.png)}");
    StoreBtn->move(850,50);

    SaveBtn = new MyPushButton;
    SaveBtn->setParent(this);
    SaveBtn->setFixedSize(Button_Size/2, Button_Size/2);
    SaveBtn->setStyleSheet("QPushButton{image: url(:/res/save.png)}");
    SaveBtn->move(950,50);

    LoadBtn = new MyPushButton;
    LoadBtn->setParent(this);
    LoadBtn->setFixedSize(Button_Size/2, Button_Size/2);
    LoadBtn->setStyleSheet("QPushButton{image: url(:/res/load.png)}");
    LoadBtn->move(1000,50);

    GameBackBtn = new MyPushButton;
    GameBackBtn->setParent(this);
    GameBackBtn->setFixedSize(Button_Size/2, Button_Size/2);
    GameBackBtn->setStyleSheet("QPushButton{image: url(:/res/game_back.png)}");
    GameBackBtn->move(1050,50);

    HelpBtn = new MyPushButton;
    HelpBtn->setParent(this);
    HelpBtn->setFixedSize(Button_Size/2, Button_Size/2);
    HelpBtn->setStyleSheet("QPushButton{image: url(:/res/help.png)}");
    HelpBtn->move(1100,50);

    SoundOnBtn = new MyPushButton;
    SoundOnBtn->setParent(this);
    SoundOnBtn->setFixedSize(Button_Size/2, Button_Size/2);
    SoundOnBtn->setStyleSheet("QPushButton{image: url(:/res/sound_on.png)}");
    SoundOnBtn->move(1150,50);

    A_Btn = new MyPushButton;
    A_Btn->setParent(this);
    A_Btn->setFixedSize(80, 90);
    A_Btn->setStyleSheet("QPushButton{image: url(:/res/A_0.png)}");
    A_Btn->move(100,5);

    B_Btn = new MyPushButton;
    B_Btn->setParent(this);
    B_Btn->setFixedSize(80, 90);
    B_Btn->setStyleSheet("QPushButton{image: url(:/res/B_0.png)}");
    B_Btn->move(180,5);

    C_Btn = new MyPushButton;
    C_Btn->setParent(this);
    C_Btn->setFixedSize(80,90);
    C_Btn->setStyleSheet("QPushButton{image: url(:/res/C_0.png)}");
    C_Btn->move(260,5);

    D_Btn = new MyPushButton;
    D_Btn->setParent(this);
    D_Btn->setFixedSize(80,90);
    D_Btn->setStyleSheet("QPushButton{image: url(:/res/D_0.png)}");
    D_Btn->move(340,5);


    E_Btn = new MyPushButton;
    E_Btn->setParent(this);
    E_Btn->setFixedSize(80,90);
    E_Btn->setStyleSheet("QPushButton{image: url(:/res/E_0.png)}");
    E_Btn->move(420,5);

    F_Btn = new MyPushButton;
    F_Btn->setParent(this);
    F_Btn->setFixedSize(80,90);
    F_Btn->setStyleSheet("QPushButton{image: url(:/res/F_0.png)}");
    F_Btn->move(500,5);

}

void PlayScene::setupRoles(){
    for (int i = 0; i < game.OurRoles.size(); /* size() 调用放在循环体内 */) {
        auto role = game.OurRoles[i];
        QString path = ":/res/_.png";
        path.insert(6, role->name);
        int ind = path.indexOf('.');

        // 如果角色的健康值小于等于 0，将状态设置为 4
        if (role->health <= 0) {
            role->state = 4;
        }

        // 根据角色状态更新路径
        path.insert(ind, QString::number(role->state));

        // 创建绘图对象
        QPainter painter1(this);
        painter1.setPen(QPen(Qt::red, 5));
        QPoint start1 = QPoint(role->posi * Cell_Size + Left_Width + 40, role->posj * Cell_Size + Up_Height + 100);
        QPoint end1 = QPoint(role->posi * Cell_Size + Left_Width + 40 + 0.025 * role->health, role->posj * Cell_Size + Up_Height + 100);
        painter1.drawLine(start1, end1);

        // 重新设置 QPainter 对象的颜色为蓝色，并绘制蓝色技能冷却条
        painter1.setPen(QPen(Qt::blue, 5));
        QPoint start2 = QPoint(role->posi * Cell_Size + Left_Width + 40, role->posj * Cell_Size + Up_Height + 110);
        QPoint end2 = QPoint(role->posi * Cell_Size + Left_Width + 40 + 0.003 * role->timer_skillcd.remainingTime(), role->posj * Cell_Size + Up_Height + 110);
        painter1.drawLine(start2, end2);

        // 处理角色的状态
        if (role->state == 4) {
            // 绘制角色图像
            painter1.drawPixmap(role->posi * Cell_Size + Left_Width, role->posj * Cell_Size + Up_Height, Cell_Size + 5, Cell_Size + 5, path);
            // 从列表中移除角色并获取下一个元素的迭代器
            game.OurRoles.removeOne(role);
            // 注意：在移除元素后，i 不递增，因为元素的数量减少了，当前的 i 可能会指向下一个元素
        }
        else
        {
         if (role->be_attacking) {
                // 绘制具有透明度的角色图像
                QPixmap pixmap(path);
                painter1.setOpacity(0.5);
                painter1.drawPixmap(role->posi*Cell_Size+Left_Width, role->posj*Cell_Size+Up_Height, Cell_Size , Cell_Size, pixmap);
                painter1.setOpacity(1.0);
            }
         else
         {
                // 绘制正常状态的角色图像
         painter1.drawPixmap(role->posi*Cell_Size+Left_Width, role->posj*Cell_Size+Up_Height, Cell_Size , Cell_Size, path);
            }


            // 遍历并绘制角色的子弹
            for (auto bullet : role->Bullets) {
                if (!bullet->is_attacking) {
                    continue;
                }
                QString name = bullet->name;
                QString path_item = ":/res/_bullet.png";
                path_item.insert(6, name);
                painter1.drawPixmap(role->posi*Cell_Size+Left_Width, role->posj*Cell_Size+Up_Height+10, (Cell_Size - 20)/2, (Cell_Size - 20) /5, path_item);
            }

            // 递增 i 以处理下一个角色
            ++i;
        }
    }
    // 遍历敌人角色列表
    for (int i = 0; i < game.EnemyRoles.size(); /* size() 调用放在循环体内 */) {
        auto role = game.EnemyRoles[i];
        QString path = ":/res/_.png";
        path.insert(6, role->name);
        int ind = path.indexOf('.');

        // 如果角色的健康值小于等于 0，将状态设置为 4
        if (role->health <= 0) {
            role->state = 4;
        }

        // 根据角色状态更新路径
        path.insert(ind, QString::number(role->state));

        // 创建绘图对象
        QPainter painter1(this);
        QPainter painterline1(this);
        painterline1.setPen(QPen(Qt::red, 5));

        // 绘制生命条
        QPoint start1 = QPoint(role->posx+40, role->posy + 100);
        QPoint end1 = QPoint(role->posx+40 + 0.025 * role->health, role->posy + 100);
        painterline1.drawLine(start1, end1);

        // 处理角色的状态
        if (role->state == 4) {
            // 绘制角色图像
            painter1.drawPixmap(role->posi * Cell_Size + Left_Width, role->posj * Cell_Size + Up_Height, Cell_Size + 5, Cell_Size + 5, path);

            // 从列表中移除角色并获取下一个元素的迭代器
            game.EnemyRoles.removeOne(role);
            // 注意：在移除元素后，i 不递增，因为元素的数量减少了，当前的 i 可能会指向下一个元素
        } else {
            if (role->be_attacking) {
                // 绘制具有透明度的角色图像
                QPixmap pixmap(path);
                painter1.setOpacity(0.5);
                painter1.drawPixmap(role->posx, role->posy, Cell_Size + 5, Cell_Size + 5, pixmap);
                painter1.setOpacity(1.0);
            } else {
                // 绘制正常状态的角色图像
                painter1.drawPixmap(role->posx, role->posy, Cell_Size + 5, Cell_Size + 5, path);
            }

            // 遍历并绘制角色的子弹
            for (auto bullet : role->Bullets) {
                if (!bullet->is_attacking) {
                    continue;
                }
                QString name = bullet->name;
                QString path_item = ":/res/_bullet.png";
                path_item.insert(6, name);
                painter1.drawPixmap(bullet->posx, bullet->posy + 40, (Cell_Size - 20)/2, (Cell_Size - 20) /5, path_item);
            }

            // 递增 i 以处理下一个角色
            ++i;
        }
    }


}

void PlayScene::setupCells(){

    QPainter painter(this);
    QString path1(":/res/game_cell.png");
    int rows =12;
    int columns =6;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            painter.drawPixmap(i * Cell_Size + Left_Width, j * Cell_Size + Up_Height, Cell_Size, Cell_Size, path1);
        }
    }
    QPen pen;
    pen.setColor(QColor(200,200,200));
    painter.setPen(pen);
    for (int y = 100; y <=100+6*Cell_Size; y += Cell_Size)
    {
        painter.drawLine(30, y, 30+12*Cell_Size, y);
    }
    for (int x =30; x <=30+12*Cell_Size; x +=Cell_Size)
    {
        painter.drawLine(x, 100, x,100+6*Cell_Size);
    }
}


void PlayScene::setupBlueRole(){
    if(SelectName!=nullptr){
        QString path=":/res/_blue.png";
        path.insert(6,SelectName);

        QPixmap pixmap(path);
        QPainter painter2(this);
        painter2.drawPixmap(SelectPos.i*Cell_Size+Left_Width,SelectPos.j*Cell_Size+Up_Height,Cell_Size-10, Cell_Size-10,pixmap);
    }
    else return;
}


void PlayScene::setupText(){
    QPainter painter4(this);
    painter4.setFont(QFont("宋体",25, QFont::Bold));
    QString text1="Score:";
    QString text2="Money:";
    painter4.drawText(30,660, text2+QString::number(game.money));
    painter4.drawText(30,this->height()-20,QString("Round")+QString::number(game.round));
    if (game.enemy_timer.remainingTime()>=190000&&game.enemy_timer.remainingTime()<=200000) {
        painter4.setFont(QFont("宋体", 30, QFont::Bold));
        painter4.setPen(Qt::red); // 设置字体颜色为红色
        painter4.drawText(300, 300, "The FIRST enemies are COMING!");
    }
    if (game.enemy_timer.remainingTime()>=140000&&game.enemy_timer.remainingTime()<=150000) {
        painter4.setFont(QFont("宋体", 30, QFont::Bold));
        painter4.setPen(Qt::red); // 设置字体颜色为红色
        painter4.drawText(300, 300, "The Second enemies are COMING!");
    }
    if (game.enemy_timer.remainingTime()>=100000&&game.enemy_timer.remainingTime()<=110000) {
        painter4.setFont(QFont("宋体", 30, QFont::Bold));
        painter4.setPen(Qt::red); // 设置字体颜色为红色
        painter4.drawText(300, 300, "The Third enemies are COMING!");
    }
    if (game.enemy_timer.remainingTime()>=50000&&game.enemy_timer.remainingTime()<=60000) {
        painter4.setFont(QFont("宋体", 30, QFont::Bold));
        painter4.setPen(Qt::red); // 设置字体颜色为红色
        painter4.drawText(300, 300, "The Last enemies are COMING!");
    }
}


void PlayScene::paintEvent(QPaintEvent *)
{

    setupCells();
    setupBlueRole();
    setupRoles();
    setupText();
    QPainter painter(this);


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
        {//如果有待放置的
            qDebug("we have role to place");
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
        if(role!=nullptr&&!role->timer_skillcd.isActive()){
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
        SelectPos.i=(x-Left_Width)/Cell_Size;
        SelectPos.j=(y-Up_Height)/Cell_Size;
    }
}
void PlayScene::EnemyCome(){
    if(game.enemy_timer.remainingTime()<50000 && game.batch <48){
        MyRole* SelectEnemy = nullptr;
        if(game.enemy_timer.remainingTime()%100==1)SelectEnemy = new Role_J(1);
        else if(game.enemy_timer.remainingTime()%100==67)SelectEnemy = new Role_H(2);
        else if(game.enemy_timer.remainingTime()%100==79)SelectEnemy = new Role_J(2);
        else if(game.enemy_timer.remainingTime()%100==43)SelectEnemy = new Role_I(3);
        else if(game.enemy_timer.remainingTime()%100==30&&game.round==2)SelectEnemy = new Role_K(3);
        else if(game.enemy_timer.remainingTime()%100==37)SelectEnemy = new Role_H(4);
        else if(game.enemy_timer.remainingTime()%100==29)SelectEnemy = new Role_J(5);
        else if(game.enemy_timer.remainingTime()%100==57)SelectEnemy = new Role_I(5);
        else if(game.enemy_timer.remainingTime()%100==23)SelectEnemy = new Role_G(3);
        else if(game.enemy_timer.remainingTime()%100==40&&game.round==2)SelectEnemy = new Role_K(3);
        else if(game.enemy_timer.remainingTime()%100==17)SelectEnemy = new Role_J(0);
        else if(game.enemy_timer.remainingTime()%100==99)SelectEnemy = new Role_H(0);
        if(SelectEnemy) {
            game.EnemyRoles.append(SelectEnemy);
            game.batch++;
        }
    }

    else if(game.enemy_timer.remainingTime() < 100000 && game.batch <35){
        MyRole* SelectEnemy = nullptr;
        if(game.enemy_timer.remainingTime()%100==1)SelectEnemy = new Role_I(1);
        else if(game.enemy_timer.remainingTime()%100==67)SelectEnemy = new Role_H(2);
        else if(game.enemy_timer.remainingTime()%100==79)SelectEnemy = new Role_G(2);
        else if(game.enemy_timer.remainingTime()%100==43)SelectEnemy = new Role_I(3);
        else if(game.enemy_timer.remainingTime()%100==37)SelectEnemy = new Role_H(4);
        else if(game.enemy_timer.remainingTime()%100==29)SelectEnemy = new Role_H(5);
        else if(game.enemy_timer.remainingTime()%100==57)SelectEnemy = new Role_I(5);
        else if(game.enemy_timer.remainingTime()%100==23)SelectEnemy = new Role_G(3);
        else if(game.enemy_timer.remainingTime()%100==17)SelectEnemy = new Role_I(0);
        else if(game.enemy_timer.remainingTime()%100==99)SelectEnemy = new Role_H(0);
        if(SelectEnemy) {
            game.EnemyRoles.append(SelectEnemy);
            game.batch++;
        }
    }
    else if(game.enemy_timer.remainingTime() < 150000 && game.batch<20){
        game.batch++;
        MyRole* SelectEnemy = nullptr;
        if(game.enemy_timer.remainingTime()%100==1)SelectEnemy = new Role_G(1);
        else if(game.enemy_timer.remainingTime()%100==67)SelectEnemy = new Role_H(2);
        else if(game.enemy_timer.remainingTime()%100==79)SelectEnemy = new Role_G(2);
        else if(game.enemy_timer.remainingTime()%100==43)SelectEnemy = new Role_I(3);
        else if(game.enemy_timer.remainingTime()%100==37)SelectEnemy = new Role_H(4);
        else if(game.enemy_timer.remainingTime()%100==29)SelectEnemy = new Role_H(5);
        else if(game.enemy_timer.remainingTime()%100==57)SelectEnemy = new Role_I(5);
        else if(game.enemy_timer.remainingTime()%100==23)SelectEnemy = new Role_G(3);
        else if(game.enemy_timer.remainingTime()%100==17)SelectEnemy = new Role_I(0);
        else if(game.enemy_timer.remainingTime()%100==99)SelectEnemy = new Role_H(0);
        if(SelectEnemy) {
            game.EnemyRoles.append(SelectEnemy);
            game.batch++;
        }
    }
    else if(game.enemy_timer.remainingTime() < 190000 && game.batch<10){

            MyRole* SelectEnemy = nullptr;
            if(game.enemy_timer.remainingTime()%100==1)SelectEnemy = new Role_G(1);
            else if(game.enemy_timer.remainingTime()%100==67)SelectEnemy = new Role_H(2);
            else if(game.enemy_timer.remainingTime()%100==79)SelectEnemy = new Role_G(2);
            else if(game.enemy_timer.remainingTime()%100==43)SelectEnemy = new Role_G(3);
            else if(game.enemy_timer.remainingTime()%100==37)SelectEnemy = new Role_H(4);
            else if(game.enemy_timer.remainingTime()%100==29)SelectEnemy = new Role_H(5);
            else if(game.enemy_timer.remainingTime()%100==57)SelectEnemy = new Role_G(5);
            else if(game.enemy_timer.remainingTime()%100==23)SelectEnemy = new Role_G(3);
            else if(game.enemy_timer.remainingTime()%100==17)SelectEnemy = new Role_G(0);
            else if(game.enemy_timer.remainingTime()%100==99)SelectEnemy = new Role_H(0);
            if(SelectEnemy) {
                game.EnemyRoles.append(SelectEnemy);
                game.batch++;
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
                if(!game.enemy_timer.isActive()&&game.game_begin==true){
                    game.game_begin=false;
                    if(game.round==1){
                        QMessageBox::information(this, "游戏结束", "First Round SUCCESS！");
                        emit First_success();
                    }
                    else{
                        QMessageBox::information(this, "游戏结束", "Second Round SUCCESS！");
                        emit Second_success();
                    }
                }
                if(game.game_begin==true){
                for(auto role:game.EnemyRoles){
                    if(role!=nullptr&&role->posx<=40){
                         game.game_begin=false;
                        if(game.round==1){
                            QMessageBox::information(this, "游戏结束", "First Round Fail！");
                            emit First_failure();

                        }
                        else{
                            QMessageBox::information(this, "游戏结束", "Second Round Fail！");
                            emit Second_failure();
                        }
                    }
                }
                }
                //这里是每隔一段时间就重绘地图和更新地图中传送带的运行
                //重新绘制图片
                update();

                for(auto role:game.OurRoles)
                    role->UpdateState(game);

                for(auto role:game.EnemyRoles){
                    qDebug()<<role->name<<role->posi<<role->posj<<"is updating";
                    role->UpdateState(game);
                }
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

