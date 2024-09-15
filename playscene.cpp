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
     StoreBtn->move(200,820);


    SaveBtn = new MyPushButton;
    SaveBtn->setParent(this);
    SaveBtn->setFixedSize(Button_Size/2, Button_Size/2);
    SaveBtn->setStyleSheet("QPushButton{image: url(:/res/save.png)}");
    SaveBtn->move(800,850);

    LoadBtn = new MyPushButton;
    LoadBtn->setParent(this);
    LoadBtn->setFixedSize(Button_Size/2, Button_Size/2);
    LoadBtn->setStyleSheet("QPushButton{image: url(:/res/load.png)}");
    LoadBtn->move(850,850);

    GameBackBtn = new MyPushButton;
    GameBackBtn->setParent(this);
    GameBackBtn->setFixedSize(Button_Size/2, Button_Size/2);
    GameBackBtn->setStyleSheet("QPushButton{image: url(:/res/game_back.png)}");
    GameBackBtn->move(900,850);

    HelpBtn = new MyPushButton;
    HelpBtn->setParent(this);
    HelpBtn->setFixedSize(Button_Size/2, Button_Size/2);
    HelpBtn->setStyleSheet("QPushButton{image: url(:/res/help.png)}");
    HelpBtn->move(950,850);

    SoundOnBtn = new MyPushButton;
    SoundOnBtn->setParent(this);
    SoundOnBtn->setFixedSize(Button_Size/2, Button_Size/2);
    SoundOnBtn->setStyleSheet("QPushButton{image: url(:/res/sound_on.png)}");
    SoundOnBtn->move(1150,850);

}
void PlayScene::setupFixedBuildings(){
    bool setHub=false;
    for(int i=0;i<24;i++){
        for(int j=0;j<16;j++){
            if(game.GameMap[i][j]!=nullptr){
                QString path=":/res/.png";
                path.insert(6,game.GameMap[i][j]);
                QPainter painter(this);
                if(game.GameMap[i][j]=="hub"){
                    if(setHub==false){
                        painter.drawPixmap(i*Cell_Size, j*Cell_Size,Cell_Size*2, Cell_Size*2,path);
                        setHub=true;
                        QString path_temp=":/res/.png";
                        path_temp.insert(6,game.target);
                        if(game.target=="mine1_l"||game.target=="mine2_l_4")
                         painter.drawPixmap(i*Cell_Size+27, j*Cell_Size+27, Cell_Size-30, Cell_Size-20,path_temp);
                        else painter.drawPixmap(i*Cell_Size+27, j*Cell_Size+27, Cell_Size,Cell_Size,path_temp);
                        painter.drawText(i*Cell_Size+35, j*Cell_Size+30, QString::number(game.score)+QString("/")+QString::number(game.success_score));
                        painter.drawText(i*Cell_Size+35, j*Cell_Size+80,"交付中心");
                    }
                    else continue;


                }
                else painter.drawPixmap(i*Cell_Size, j*Cell_Size,Cell_Size, Cell_Size,path);
            }
        }
    }
}
void PlayScene::setupBuildings(){
    for(auto building:game.Buildings){
            QString path=":/res/_.png";
            path.insert(6,building->name);
            int ind=path.indexOf('.');
            QPainter painter1(this);
            if(building->name=="painter"||building->name=="cutter"){
                        switch (building->direction)
                        {
                        case UP:
                            path.insert(ind,"W");
                            painter1.drawPixmap(building->posi*Cell_Size, building->posj*Cell_Size,Cell_Size * 2, Cell_Size,path);
                            break;
                        case DOWN:
                             path.insert(ind,"S");
                            painter1.drawPixmap(building->posi * Cell_Size, building->posj * Cell_Size, Cell_Size * 2 ,Cell_Size,path);
                            break;
                        case LEFT:
                             path.insert(ind,"A");
                            painter1.drawPixmap(building->posi *Cell_Size, building->posj*Cell_Size, Cell_Size, Cell_Size*2, path);
                            break;
                        case RIGHT:
                             path.insert(ind,"D");
                           painter1.drawPixmap(building->posi *Cell_Size, building->posj *Cell_Size, Cell_Size, Cell_Size*2, path);
                            break;
                        default:
                            break;
                        }
                    }
                if(building->name=="trash"||building->name=="miner"){
                        switch (building->direction)
                        {
                        case UP:
                            path.insert(ind,"W");
                            break;
                        case DOWN:
                            path.insert(ind,"S");
                            break;
                        case LEFT:
                            path.insert(ind,"A");
                            break;
                        case RIGHT:
                            path.insert(ind,"D");
                            break;
                        default:
                            break;
                        }
                        painter1.drawPixmap(building->posi *Cell_Size, building->posj*Cell_Size, Cell_Size, Cell_Size, path);
                }
                if(building->name=="belt"){
                    switch(building->direction){
                    case 1:
                        path.insert(ind,"W");
                        break;
                    case 2:
                        path.insert(ind,"S");
                        break;
                    case 3:
                        path.insert(ind,"A");
                        break;
                    case 4:
                        path.insert(ind,"D");
                        break;
                    case 5:
                        path.insert(ind,"A_W");
                        break;
                    case 6:
                        path.insert(ind,"S_D");
                        break;
                    case 7:
                        path.insert(ind,"D_W");
                        break;
                    case 8:
                        path.insert(ind,"S_A");
                        break;
                    case 9:
                        path.insert(ind,"A_S");
                        break;
                    case 10:
                        path.insert(ind,"W_D");
                        break;
                    case 11:
                        path.insert(ind,"D_S");
                        break;
                    case 12:
                        path.insert(ind,"W_A");
                        break;
                    default:
                        break;
                    }
                    painter1.drawPixmap(building->posi *Cell_Size, building->posj*Cell_Size, Cell_Size, Cell_Size, path);
                    if(building->item!=nullptr){//画出传送带上的物体
                        QString name=building->item->name;
                        qDebug()<<name<<"line 230";
                        QString path_item=":/res/_item.png";
                        path_item.insert(6,name);
                        qDebug()<<path_item<<"line 232";
                        if(name.contains("_l")){
                            painter1.drawPixmap(building->item->posx+10,building->item->posy,Cell_Size-30, Cell_Size-20, path_item);
                        }

                        else if(name.contains("_r")){
                             painter1.drawPixmap(building->item->posx+20,building->item->posy+10,Cell_Size-30, Cell_Size-20, path_item);
                            }

                        else painter1.drawPixmap(building->item->posx+10,building->item->posy,Cell_Size-20, Cell_Size-20, path_item);
                    }
      }

}
}
void PlayScene::setupCells(){
    QPen pen;
    pen.setColor(QColor(200,200,200));
    QPainter painter(this);
    painter.setPen(pen);
    for (int y = 0; y <=Play_Height-Prop_Widget_Height; y += Cell_Size)
    {
       painter.drawLine(0, y, Play_Width, y);
    }
    for (int x = 0; x <Play_Width; x +=Cell_Size)
    {painter.drawLine(x, 0, x, Play_Height-Prop_Widget_Height);
    }
}
void PlayScene::setupBlueBuilding(){
    if(SelectName!=nullptr){
        QString path=":/res/_blue_.png";
        path.insert(6,SelectName);
        int ind=path.indexOf('.');
        path.insert(ind,SelectDirection);
        QPixmap pixmap(path);
        QPainter painter2(this);
        Selectw=Cell_Size,Selecth=Cell_Size;
        if(SelectName=="cutter"||SelectName=="painter"){
            if(SelectDirection=="A"||SelectDirection=="D"){
                Selecth=Cell_Size*2;
            }
            if(SelectDirection=="W"||SelectDirection=="S"){
               Selectw=Cell_Size*2;
            }
        }

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
    painter4.drawText(30,this->height()-20,QString("Level")+QString::number(game.level));
}
void PlayScene::paintEvent(QPaintEvent *)
{

    setupCells();
    setupFixedBuildings();
    setupBlueBuilding();
    setupBuildings();
    setupText();
    connect(helpScene,&HelpScene::HelpSceneback,this,[=](){
        helpScene->hide();
        this->show();
    });
    connect(upgradeScene,&UpgradeScene::UpgradeSceneback_belt,this,[=](){
        if(1200<1500/(1+store_belt))game.belt_spd=1200;
        else game.belt_spd=1500/(1+store_belt);
        upgradeScene->hide();
        this->show();
    });
    connect(upgradeScene,&UpgradeScene::UpgradeSceneback_cutter,this,[=](){
        game.cutter_spd-=400;
        upgradeScene->hide();
        this->show();
    });
    connect(upgradeScene,&UpgradeScene::UpgradeSceneback_miner,this,[=](){
        game.miner_spd-=400;
        upgradeScene->hide();
        this->show();
    });
    connect(storeScene,&StoreScene::StoreSceneback_money,this,[=](){
        disconnect(storeScene, &StoreScene::StoreSceneback_money, this, nullptr);
        upgradeScene->hide();
        this->show();
        if(game.money>=20){
            game.money-=20;
            this->store_money++;
            this->game.money_plus++;
            QMessageBox::information(this, "Store", "Buy successfully!");
        }
        else QMessageBox::information(this, "Store", "No enough money");
    });
    connect(storeScene,&StoreScene::StoreSceneback_belt,this,[=](){
        disconnect(storeScene, &StoreScene::StoreSceneback_belt, this, nullptr);
        upgradeScene->hide();
        this->show();
        if(game.money>=30){
            game.money-=30;
            this->store_belt++;
            game.belt_spd=1500/(1+store_belt);
            QMessageBox::information(this, "Store", "Buy successfully!");
        }
        else QMessageBox::information(this, "Store", "No enough money");
    });
    connect(storeScene,&StoreScene::StoreSceneback_cutter,this,[=](){
        disconnect(storeScene, &StoreScene::StoreSceneback_cutter, this, nullptr);
        upgradeScene->hide();
        this->show();
        if(game.money>=40){
            this->store_cutter++;
            game.money-=40;
            game.cutter_spd=2000/(1+store_cutter);
            QMessageBox::information(this, "Store", "Buy successfully!");
        }
        else QMessageBox::information(this, "Store", "No enough money");
    });

    if(game.score>=game.upgrade_score){
        game.upgrade_score=1000;
        game.level++;
        this->hide();
        upgradeScene->show();
    }
    if((game.score>=game.success_score)&&game.round==1){
        game.success_score=1000;
        emit First_success();

    }
    if(game.score>=game.success_score&&game.round==2){

        emit Second_success();
         game.success_score=1000;
    }

}
void PlayScene::mousePressEvent(QMouseEvent *event)
{

    //把鼠标点击的监听放在playscene
    int click_x = event->pos().x();
    int click_y = event->pos().y();
    if (event->button() == Qt::LeftButton)
    {
        if (SelectName!=nullptr)
        {//如果有待放置的建筑物的名字
             int direction=1;
            if(SelectDirection=="W")direction=1;
            if(SelectDirection=="S")direction=2;
            if(SelectDirection=="A")direction=3;
            if(SelectDirection=="D")direction=4;
            if(SelectName=="cutter"){
               Selectbuilding=new Cutter(SelectPos.i/Cell_Size,SelectPos.j/Cell_Size,SelectName,direction);
            }

            if(SelectName=="painter") Selectbuilding=new Painter(SelectPos.i/Cell_Size,SelectPos.j/Cell_Size,SelectName,direction);

            if(SelectName=="trash")Selectbuilding=new Trash(SelectPos.i/Cell_Size,SelectPos.j/Cell_Size,SelectName,direction);
            if(SelectName=="belt"){
                if(SelectDirection=="A_W")direction=5;
                if(SelectDirection=="S_D")direction=6;
                if(SelectDirection=="D_W")direction=7;
                if(SelectDirection=="S_A")direction=8;
                if(SelectDirection=="A_S")direction=9;
                if(SelectDirection=="W_D")direction=10;
                if(SelectDirection=="D_S")direction=11;
                if(SelectDirection=="W_A")direction=12;
            Selectbuilding=new Belt(SelectPos.i/Cell_Size,SelectPos.j/Cell_Size,SelectName,direction);
            }
            if(SelectName=="miner")Selectbuilding=new Miner(SelectPos.i/Cell_Size,SelectPos.j/Cell_Size,SelectName,direction);
            if (Selectbuilding->CanPlace(GridVec(SelectPos.i/Cell_Size,SelectPos.j/Cell_Size),game)){
                if(SelectName=="miner"){
                    ((Miner*)Selectbuilding)->sourcename=game.GameMap[SelectPos.i/Cell_Size][SelectPos.j/Cell_Size];
                     game.Buildings.push_back(Selectbuilding);
                    return;                //miner将不记录在地图中，只压入建筑物列表,并记录矿物名称
                }
                game.Buildings.push_back(Selectbuilding);
                 for(auto pos:Selectbuilding->AllPos())game.GameMap[pos.i][pos.j]=SelectName;

            }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        SelectName.clear();
        game.RemoveBuilding(GridVec(click_x/Cell_Size,click_y/Cell_Size));
        update();
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
void PlayScene::BeginUpdate()
{//工厂开始动
    timer.start(50);
    // 监听定时器
    connect(&timer, &QTimer::timeout, this, [=]()
            {//这里是每隔一段时间就重绘地图和更新地图中传送带的运行
                //重新绘制图片
         update();
        if(!game.Buildings.empty()){
             for(auto building:game.Buildings)
                 building->UpdateState(game);
         }
    });
}
void PlayScene::keyPressEvent(QKeyEvent *event)
{//只需要改变Selectrent_building_direct的方位
    if(SelectName==nullptr)return;
    switch (event->key())
    {
    case Qt::Key_W:
        SelectDirection="W";
        break;
    case Qt::Key_S:
        SelectDirection="S";
        break;
    case Qt::Key_A:
        SelectDirection="A";
        break;
    case Qt::Key_D:
        SelectDirection="D";
        break;
    case Qt::Key_Q:
        SelectDirection="A_W";
        break;
    case Qt::Key_E:
        SelectDirection="S_D";
        break;
    case Qt::Key_Z:
        SelectDirection="D_W";
        break;
    case Qt::Key_C:
        SelectDirection="S_A";
        break;
    case Qt::Key_L:
        SelectDirection="A_S";
        break;
    case Qt::Key_R:
        SelectDirection="W_D";
        break;
    case Qt::Key_U:
        SelectDirection="D_S";
        break;
    case Qt::Key_G:
        SelectDirection="W_A";
        break;
    default:
        break;
    }
}
void PlayScene::saveGame() {
    QFile file("savegame.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out<<game.score << "\n";
        out <<game.round<< "\n";
        out <<game.level<< "\n";
        out<<game.money<<"\n";
        out << game.Buildings.size();
        for (const MyBuilding *building :game.Buildings) {
            out<<building->name<<"\n";
            out<<building->posi<<"\n";
            out<<building->posj<<"\n";
            out<<building->direction<<"\n";
        }
        file.close();
        QMessageBox::information(this, "Save Game", "Game saved successfully!");
    } else {
        QMessageBox::warning(this, "Save Game", "Failed to save game!");
    }
}
void PlayScene::loadGame() {
    QFile file("savegame.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int score,round,level,money;
        in >> score;
        in >> round;
        in >> level;
        in >> money;
        game.money=money;
        game.level=level;
        game.score=score;
        game.round=round;
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 16; ++j) {
                game.GameMap[i][j] = QString();
            }
        }
        if(round==1)game.FirstGame();
        if(round==2)game.SecondGame();
        int numBuildings;
        in >> numBuildings;
        while(!game.Buildings.empty())game.Buildings.pop_back();
        MyBuilding*lbuild;
        for (int i = 0; i < numBuildings; ++i) {
            QString l_name;
            int l_posi,l_posj,l_direction;
            in>>l_name;
            in>>l_posi;
            in>>l_posj;
            in>>l_direction;
            if(l_name=="cutter")lbuild=new Cutter(l_posi,l_posj,l_name,l_direction);
            else if(l_name=="trash")lbuild=new Trash(l_posi,l_posj,l_name,l_direction);
            else if(l_name=="miner")lbuild=new Miner(l_posi,l_posj,l_name,l_direction);
            else if(l_name=="belt")lbuild=new Belt(l_posi,l_posj,l_name,l_direction);
            else if(l_name=="painter")lbuild=new Painter(l_posi,l_posj,l_name,l_direction);

            if(l_name=="miner"){
                ((Miner*)lbuild)->sourcename=game.GameMap[l_posi][l_posj];
                game.Buildings.push_back(lbuild);
                             //miner将不记录在地图中，只压入建筑物列表,并记录矿物名称
            }
            else {
                game.Buildings.push_back(lbuild);
            for(auto pos:lbuild->AllPos())game.GameMap[pos.i][pos.j]=l_name;
            }
        }
        file.close();
        QMessageBox::information(this, "Load Game", "Game loaded successfully!");
    } else {
        QMessageBox::warning(this, "Load Game", "Failed to load game!");
    }
}

