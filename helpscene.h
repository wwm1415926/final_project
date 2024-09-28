#ifndef HELPSCENE_H
#define HELPSCENE_H
#include <QMainWindow>
#include<mypushbutton.h>
#include<QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVector>
#include<game.h>
class HelpScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelpScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void setupback();
    int which=-1;
    MyPushButton*backBtn;
    MyPushButton *toggleButton;
    QLabel *textBox1;
    QLabel *textBox2;
    QLabel *textBox3;
    QLabel *picture;
    QVBoxLayout *mainLayout;
    QPixmap pixture;
    QLabel *pict[5];
    QLabel *textbox[5];
    bool buttonsVisible = true;
    QVector<QPushButton *> roleButtons;
    QPushButton *enmeybtn;
    QList<QRect> rects;
    const QStringList imagePaths = {
                                    ":/res/A_help.png", ":/res/B_help.png", ":/res/C_help.png", ":/res/D_help.png",
                                    ":/res/E_help.png", ":/res/F_help.png", ":/res/G_help.png", ":/res/H_help.png",
                                    ":/res/I_help.png", ":/res/J_help.png", ":/res/K_help.png"};
    const QStringList imagePaths_ = {
                                     ":/res/A_6.png", ":/res/B_6.png", ":/res/C_6.png", ":/res/D_6.png",
                                     ":/res/E_6.png", ":/res/F_6.png", ":/res/G_6.png", ":/res/H_6.png",
                                     ":/res/I_6.png", ":/res/J_6.png", ":/res/K_6.png"};
private slots:
    void toggleButtons();
    void setBackgroundImage(int index);

signals:
    //写一个信号告诉游戏场景，选择了升级
    void HelpSceneback();
};


#endif // HELPSCENE_H
