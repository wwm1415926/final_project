#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

void f(char *filename)
{ ifstream file(filename);
    if (file.fail())
        throw filename; //生成异常对象
}
int main()
{  char str[100];
    try { f(str); } //启动异常处理机制
    catch (char *fn) //后面紧跟catch,随时捕获异常对象
    { ...... //处理异常
    }
    void g()
    { ......
        try
        { f();
        }
        catch (int) //处理函数f中的throw 1;
        { <语句序列1>
        }
        catch (double) //处理函数f中的throw 1.0
        { <语句序列2>
        }
        catch (char *) //处理函数f中的throw "abcd"
        { <语句序列3>
        }
        <非catch语句>
