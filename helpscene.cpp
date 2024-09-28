#include "helpscene.h"


HelpScene::HelpScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(1200,720);
    this->setWindowTitle("帮助界面");
    setupback();
    connect(backBtn,&QPushButton::clicked,[=](){
        emit this->HelpSceneback();
    });
    connect(toggleButton, &QPushButton::clicked, this, &HelpScene::toggleButtons);
    for (int i = 0; i < 6; ++i)
    {
        connect(roleButtons[i],&QPushButton::clicked,this,[=](){
            setBackgroundImage(i);
        });
    }
    connect(enmeybtn,&QPushButton::clicked,[=](){
        setBackgroundImage(6);
    });
}
void HelpScene::setupback(){
    this->setStyleSheet(QString("background-image: url(:/res/help_A.png);"));
    picture = new QLabel();
    picture->setParent(this);
    picture->move(300,0);
    picture->setStyleSheet("background: transparent;");

    textBox1 = new QLabel();
    textBox1->move(50,0);
    textBox1->setParent(this);
    textBox1->setStyleSheet("background: transparent;");

    textBox2 = new QLabel();
    textBox2->move(200,0);
    textBox2->setParent(this);
    textBox2->setStyleSheet("background: transparent;");

    textBox3 = new QLabel();
    textBox3->move(40,300);
    textBox3->setParent(this);
    textBox3->setStyleSheet("background: transparent;");

    backBtn = new MyPushButton;
    backBtn->setParent(this);
    backBtn->setFixedSize(Button_Size, Button_Size);
    backBtn->setStyleSheet("QPushButton{image: url(:/res/back.png)}");
    backBtn->move(1100,640);

    toggleButton = new MyPushButton;
    toggleButton->setParent(this);
    toggleButton->setFixedSize(Button_Size, Button_Size);
    toggleButton->setStyleSheet("QPushButton{image: url(:/res/toggle.png)}");
    toggleButton->move(1100, 10);

    for (int i = 0; i < 6; ++i)
    {
        QPushButton *button = new QPushButton();
        button->setIcon(QPixmap(imagePaths_[i]).scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 假设头像为64x64
        button->setIconSize(QSize(64, 64));
        button->setFixedSize(64,64);
        button->setParent(this);
        button->move(80*i+10,10);
        roleButtons.append(button);
    }
    enmeybtn = new QPushButton();
    enmeybtn->setParent(this);
    enmeybtn->setFixedSize(64, 64);
    enmeybtn->setStyleSheet("QPushButton{image: url(:/res/G_help.png)}");
    enmeybtn->move(490, 10);
    roleButtons.append(enmeybtn);
    roleButtons.append(backBtn);
    for(int i=0;i<5;i++){
        pict[i]=new QLabel();
        pict[i]->setParent(this);
        pict[i]->setFixedSize(64,64);
        pict[i]->move(50,130+120*i);
        pict[i]->setPixmap(QPixmap(imagePaths[i+6]).scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        pict[i]->hide();
    }
    picture->show();



    for(int i=0;i<5;i++){
        textbox[i]=new QLabel();
        textbox[i]->setParent(this);
        textbox[i]->setStyleSheet("QLabel { font-family: 'MingLiU'; font-size: 28px; background: transparent;color：black}");
        textbox[i]->setFixedSize(1000,80);
        textbox[i]->move(140,120+120*i);
        textbox[i]->hide();
    }


    textbox[0]->setText("源石虫   生命值  1050  攻击力  150  移动速度  1  攻击间隔  1.2s\n攻击范围（被阻挡时攻击）：单格");
    textbox[1]->setText("弩手   生命值  1850  攻击力  350  移动速度1  攻击间隔  2.0s\n攻击范围（优先攻击血量最少单位）:");
    textbox[2]->setText("妖怪   生命值  1600  攻击力  220  移动速度1  攻击间隔  2.5s\n攻击范围：");
    textbox[3]->setText("重装防御者   生命值  6000  攻击力  600  移动速度  1  攻击间隔  2.6s\n攻击范围（被阻挡时攻击）：单格");
    textbox[4]->setText("伐木机   生命值  7000  攻击力  700  移动速度  1  攻击间隔  3.0s\n攻击范围（被阻挡时攻击）：单格");
}
void HelpScene::paintEvent(QPaintEvent *){
    QPainter painter(this);

    rects.clear();
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    if(which==0){
        painter.drawRect(150,646,20,20);
        rects.append(QRect(175,646,20,20));
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
    }else if(which==1){
        painter.drawRect(150,549,20,20);
        painter.drawRect(60,659,20,20);
        for(int i = 1;i<4;i++){
            rects.append(QRect(60+25*i,659,20,20));
            rects.append(QRect(60+25*i,684,20,20));
            rects.append(QRect(60+25*i,634,20,20));
            rects.append(QRect(150+25*i,549,20,20));
        }
        rects.append(QRect(60,634,20,20));
        rects.append(QRect(60,684,20,20));
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);

    }else if(which==2){
        painter.drawRect(150,610,20,20);
        for(int i = 1;i<5;i++){
            rects.append(QRect(150+25*i,610,20,20));
        }
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);

    }else if(which==3){
        painter.drawRect(150,610,20,20);
        for(int i = 1;i<4;i++){
            rects.append(QRect(150+25*i,610,20,20));
        }
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
    }else if(which==4){
        painter.drawRect(150,603,20,20);
        rects.append(QRect(175,603,20,20));
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
    }else if(which==5){
        painter.drawRect(150,631,20,20);
        for(int i = 1;i<5;i++){
            rects.append(QRect(150+25*i,606,20,20));
            rects.append(QRect(150+25*i,631,20,20));
            rects.append(QRect(150+25*i,656,20,20));
        }
        rects.append(QRect(150,606,20,20));
        rects.append(QRect(150,656,20,20));
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
    }else if(which==6){
        painter.drawRect(315,430,20,20);
        painter.drawRect(710,290,20,20);
        for(int i = 0;i<4;i++){
            rects.append(QRect(610+25*i,290,20,20));
        }
        for(int i = 1;i<4;i++){
            rects.append(QRect(290,380+25*i,20,20));
        }
        rects.append(QRect(315,405,20,20));
        rects.append(QRect(315,455,20,20));
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
    }
    painter.drawRects(rects);

}

void HelpScene::toggleButtons()
{
    buttonsVisible = !buttonsVisible;
    for (QPushButton *button : roleButtons)
    {
        button->setVisible(buttonsVisible);
    }

}

void HelpScene::setBackgroundImage(int index)
{
    for(int i=0;i<5;i++){
        pict[i]->hide();
        textbox[i]->hide();
    }

    picture->show();

    textBox1->show();
    textBox2->show();
    textBox3->show();

    which = index;
    if (index == 0){
        this->setStyleSheet(QString("background-image: url(:/res/help_A.png);"));
        pixture = QPixmap(":/res/A_help.png").scaled(968, 968, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        picture->move(250,-100);
        picture->resize(968, 968);

        textBox1->move(50,-10);
        textBox1->setText("桃\n金\n娘");
        textBox1->setStyleSheet("QLabel { font-family: 'KaiTi'; font-size: 72px; background: transparent;color: purple;}");

        textBox2->move(200,-10);
        textBox2->setText("先\n锋");
        textBox2->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 48px; background: transparent;color: purple;}");

        textBox3->move(40,280);
        textBox3->setText("生命值  1500\n攻击力  500\n攻击间隔  1s\n初始部署费用  8 \n技能  停止攻击，在8s内恢复\n      10部署点数\n技能cd  15s\n\n每5s恢复1部署点\n\n攻击范围");
        textBox3->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 20px; background: transparent;color: purple;}");

    }else if(index == 1){
        this->setStyleSheet(QString("background-image: url(:/res/help_A.png);"));
        pixture = QPixmap(":/res/B_help.png").scaled(968, 968, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        picture->move(200,-100);
        picture->resize(968,968);

        textBox1->move(30,-20);
        textBox1->setText("夕");
        textBox1->setStyleSheet("QLabel { font-family: 'SimSun'; font-size: 108px; background: transparent;}");

        textBox2->move(200,-10);
        textBox2->setText("术\n士");
        textBox2->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 48px; background: transparent;color: black;}");

        textBox3->move(40,250);
        textBox3->setText("生命值  1800\n攻击力  900\n攻击间隔  2.9s\n初始部署费用  30\n技能  攻击范围扩大，攻击\n      间隔变为2.5s，持续15s\n技能cd  20s\n\n攻击范围\n\n攻击范围（技能态）\n");
        textBox3->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 20px; background: transparent;color: black;}");


    }else if(index == 2){
        pixture = QPixmap(":/res/C_help.png").scaled(1024, 1024, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setStyleSheet(QString("background-image: url(:/res/help_C.png);"));
        picture->move(200,-100);
        picture->resize(1024, 1024);

        textBox1->move(50,0);
        textBox1->setText("白\n金");
        textBox1->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 72px; background: transparent;}");

        textBox2->move(200,0);
        textBox2->setText("狙\n击");
        textBox2->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 48px; background: transparent;color: gray;}");

        textBox3->move(40,270);
        textBox3->setText("生命值  1550\n攻击力  500\n攻击间隔  1.2s\n初始部署费用  12\n技能  攻击力+100%，攻击间隔\n      变为1.6s，持续时间无限\n技能cd  20s\n\n攻击范围");
        textBox3->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 20px; background: transparent;color: black;}");

    }else if(index == 3){
        pixture = QPixmap(":/res/D_help.png").scaled(932,932, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setStyleSheet(QString("background-image: url(:/res/help_C.png);"));
        picture->move(250,-100);
        picture->resize(932,932);

        textBox1->move(50,0);
        textBox1->setText("提\n丰");
        textBox1->setStyleSheet("QLabel { font-family: 'Microsoft JhengHei'; font-size: 72px; background: transparent;}");

        textBox2->move(200,0);
        textBox2->setText("狙\n击");
        textBox2->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 48px; background: transparent;color: gray;}");

        textBox3->move(40,270);
        textBox3->setText("生命值  1700\n攻击力  1000\n攻击间隔  2.4s\n初始部署费用  24\n技能  攻击力+40%，每次攻击发射\n      两支箭矢，晕眩目标1秒。持续10s\n技能cd  20s\n\n攻击范围");
        textBox3->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 20px; background: transparent;color: black;}");

    }else if(index == 4){
        pixture = QPixmap(":/res/E_help.png").scaled(968, 968, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setStyleSheet(QString("background-image: url(:/res/help_C.png);"));
        picture->move(250,-150);
        picture->resize(968, 968);

        textBox1->move(50,0);
        textBox1->setText("极\n光");
        textBox1->setStyleSheet("QLabel { font-family: 'NSimSun'; font-size: 72px; background: transparent;}");

        textBox2->move(200,0);
        textBox2->setText("重\n装");
        textBox2->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 48px; background: transparent;color: gray;}");

        textBox3->move(40,250);
        textBox3->setText("生命值  3500\n攻击力  900\n攻击间隔  1.6s\n初始部署费用  25\n技能  收到伤害减少15%，技能\n      持续时间过后恢复10%生命值\n      上限的生命值\n技能cd  20s\n\n攻击范围");
        textBox3->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 20px; background: transparent;color: black;}");

    }else if(index == 5){
        pixture = QPixmap(":/res/F_help.png").scaled(792, 792, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setStyleSheet(QString("background-image: url(:/res/help_C.png);"));
        picture->move(270,-20);
        picture->resize(792,792);

        textBox1->move(50,0);
        textBox1->setText("白\n面\n鸮");
        textBox1->setStyleSheet("QLabel { font-family: 'MingLiU'; font-size: 72px; background: transparent;}");

        textBox2->move(200,0);
        textBox2->setText("治\n疗");
        textBox2->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 48px; background: transparent;color: gray;}");

        textBox3->move(40,290);
        textBox3->setText("生命值  1650\n攻击力  0\n初始部署费用  13\n技能  攻击范围内队友瞬时\n      回复500生命值\n技能cd  20s\n\n攻击范围");
        textBox3->setStyleSheet("QLabel { font-family: 'Microsoft YaHei'; font-size: 20px; background: transparent;color: black;}");

    }else if(index==6){
        for(int i=0;i<5;i++){
            pict[i]->show();
        }
        this->setStyleSheet(QString("background-image: url(:/res/help_A.png);"));
        picture->hide();

        textBox1->hide();
        textBox2->hide();
        textBox3->hide();

        for(int i=0;i<5;i++){
            textbox[i]->show();
        }

    }
    qDebug()<<index<< "hi";
    picture->setPixmap(pixture);


    //textBox->setText(QString("这是角色 %1").arg(index + 'A'));
}

