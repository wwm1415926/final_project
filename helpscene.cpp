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
}
void HelpScene::setupback(){
    backBtn = new MyPushButton;
    backBtn->setParent(this);
    backBtn->setFixedSize(Button_Size, Button_Size);
    backBtn->setStyleSheet("QPushButton{image: url(:/res/back.png)}");
    backBtn->move(1100,800);
}
void HelpScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QImage background(":/res/help_background.png");
    painter.drawImage(QRect(0, 0, 1200, 900), background);
    painter.setFont(QFont("Arial", 18, QFont::Bold));
    painter.setPen(Qt::black);
    // 绘制标题
    QString title = "###################游玩说明#######################";
    QFontMetrics fm(painter.font());
    int titleWidth = fm.horizontalAdvance(title);
    painter.drawText((width() - titleWidth) / 2, 100, title);
    // 绘制说明文字
    QStringList instructions = {
        "利用道具得到交付中心需要的矿产资源，可获得金币并通关",
        "",
        "采矿机：放置在有矿产的方格，提取矿产。可通过W与S，A与D选择方向",
        "",
        "传送带：运送矿产。可通过W与S，A与D，Q与E，Z与C，L与R，U与G这六组按键选择方向",
        "",
        "切割机：可切割中心对称的矿产。可通过W与S，A与D选择方向",
        "",
        "垃圾桶：回收矿产。可通过W与S，A与D选择方向",
        "",
        "染色器：一端进颜料矿产，一端进灰色矿产，产出被染色后的矿产。可通过W与S，A与D选择方向"
        "",
        "鼠标右键可以撤销选中或删除建筑。只能存读一个档，多次存档会覆盖之前存档"
    };
    int y = 200;
    for (const QString& line : instructions) {
        int lineWidth = fm.horizontalAdvance(line);
        painter.drawText((width() - lineWidth) / 2, y, line);
        y += fm.height() + 10; // 行间距
    }
}

