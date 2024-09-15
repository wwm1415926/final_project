#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H
#include <QMainWindow>
#include<playscene.h>
#include<QWindow>
class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:

    explicit ChooseScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    PlayScene*playScene=NULL;
    /*
     * 控制第二关是否解锁
     */
    bool second_game;
signals:
    //返回主场景的信号
    void chooseSceneBack();
};

#endif // CHOOSESCENE_H
