#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QRgb>

#ifndef DBG
    #define DBG qDebug()<<"[ "<<__FILE__<<": line "<<__LINE__<< " ] "
#endif

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void Initial();
    void InitialTest();
    void setScore();
    void setColor();
    void setNum();
    void setNumTset();
    void startGame();
    void generateNum();
    int countEmpty();
    void keyPressEvent(QKeyEvent *event);
    void getBoard();
    void leftMerge();
    int leftCount(int row);
    void rightMerge();
    int rightCount(int row);
    void upMerge();
    int upCount(int col);
    void downMerge();
    int downCount(int col);
    void updateScore();
    void updateBoard();
private slots:
    void on_pbt_restart_clicked();

    void on_pbt_exit_clicked();

private:
    Ui::Widget *ui;
    int score;
    QList<QLabel *> num;
    int board[4][4];
    bool temp[16];
    bool canmove;
    int colorTab[12][3];

};

#endif // WIDGET_H
