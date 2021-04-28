#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QPalette>
#include <qmath.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->num<<ui->lab_num1<<ui->lab_num2<<ui->lab_num3<<ui->lab_num4<<ui->lab_num5<<ui->lab_num6
            <<ui->lab_num7<<ui->lab_num8<<ui->lab_num9<<ui->lab_num10<<ui->lab_num11<<ui->lab_num12
               <<ui->lab_num13<<ui->lab_num14<<ui->lab_num15<<ui->lab_num16;
    Initial();
    this->grabKeyboard();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::setNum()
{




    for(int i=0;i<num.size();i++){
        num[i]->setText(QString(""));
        num[i]->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
        num[i]->setStyleSheet("QLabel{font-size:45px;}");
        colorTab[0][0]=0xcc;colorTab[0][1]=0xc0;colorTab[0][2]=0xb2;
        QPalette palette;
        palette.setColor(QPalette::Background,QColor(colorTab[0][0],colorTab[0][1],colorTab[0][2]));
        num[i]->setAutoFillBackground(true);
        num[i]->setPalette(palette);
        num[i]->setFixedSize(num[i]->width(),num[i]->width());
        temp[i]=true;
    }
}

void Widget::setNumTset()
{
    this->num<<ui->lab_num1<<ui->lab_num2<<ui->lab_num3<<ui->lab_num4<<ui->lab_num5<<ui->lab_num6
            <<ui->lab_num7<<ui->lab_num8<<ui->lab_num9<<ui->lab_num10<<ui->lab_num11<<ui->lab_num12
               <<ui->lab_num13<<ui->lab_num14<<ui->lab_num15<<ui->lab_num16;


    for(int i=0;i<num.size();i++){
        num[i]->clear();
        num[i]->setText(QString(""));
        num[i]->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
        num[i]->setStyleSheet("QLabel{font-size:45px;}");
//        QPalette palette;
//        palette.setColor(QPalette::Background,QColor(colorTab[0][0],colorTab[0][1],colorTab[0][2]));
        num[i]->setAutoFillBackground(true);
       // num[i]->setPalette(palette);
        num[i]->setFixedSize(num[i]->width(),num[i]->width());
        temp[i]=true;
    }
}
void Widget::startGame()
{
     DBG<<"123"<<endl;
     setColor();
     int index1,index2;
     int num1,num2;
     //随机生成位置（16个方格，0~15编号）
     index1 = qrand()%16;
     index2 = qrand()%16;
     while(index2 == index1)
     {
         index2 = qrand()%16;
     }
     //随机生成2或4(随机生成0,1，则0代表2,1代表4)
     num1 = qrand()%2==0 ? 2 : 4;
     num2 = qrand()%2==0 ? 2 : 4;
     num[index1]->setText(QString::number(num1));
     num[index1]->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
     num[index1]->setStyleSheet("QLabel{font-size:45px;}");
     QPalette palette;
     int id1=qLn(num1)/qLn(2);
     palette.setColor(QPalette::Background,QColor(colorTab[id1][0],colorTab[id1][1],colorTab[id1][2]));
     num[index1]->setAutoFillBackground(true);
     num[index1]->setPalette(palette);
     num[index2]->setText(QString::number(num2));
     num[index2]->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
     num[index2]->setStyleSheet("QLabel{font-size:45px;}");
     int id2=qLn(num2)/qLn(2);
     palette.setColor(QPalette::Background,QColor(colorTab[id2][0],colorTab[id2][1],colorTab[id2][2]));
     num[index2]->setAutoFillBackground(true);
     num[index2]->setPalette(palette);
     temp[index1]=false;
     temp[index2]=false;

}
void Widget::keyPressEvent(QKeyEvent *event){
    switch(event->key())
         {
         case Qt::Key_Up:
            upMerge();
            generateNum();
             break;
         case Qt::Key_Down:
            downMerge();
            generateNum();
             break;
         case Qt::Key_Left:
            leftMerge();
            generateNum();
             break;
         case Qt::Key_Right:
            rightMerge();
            generateNum();
             break;
         default:
             //QGraphicsView::keyPressEvent(event);
             break;
         }
    updateScore();
}
void Widget::leftMerge()
{
    canmove=countEmpty()>0;
    if(!canmove){
        QMessageBox::information(this,QStringLiteral("失败"),QStringLiteral("游戏结束，再接再厉！"));
        return;
    }
    getBoard();
    for(int i=0;i<4;i++){
        int cnt=leftCount(i);
        QList<int> vec;
        for(int j=cnt;j<4;j++){
            if(board[i][j]>=2){
                vec<<board[i][j];
            }
        }
        int sz=vec.size();
        if(sz==0){
            continue;
        }else if(sz==1){
            board[i][0]=vec[0];
            board[i][1]=0;
            board[i][2]=0;
            board[i][3]=0;
        }else if(sz==2){
            if(vec[0]==vec[1]){
                board[i][0]=2*vec[0];
                board[i][1]=0;
            }else{
                board[i][0]=vec[0];
                board[i][1]=vec[1];
            }
            board[i][2]=0;
            board[i][3]=0;
        }else if(sz==3){
            if(vec[0]==vec[1]){
                board[i][0]=2*vec[0];
                board[i][1]=vec[2];
                board[i][2]=0;
                board[i][3]=0;
            }else if(vec[1]==vec[2]){
                board[i][0]=vec[0];
                board[i][1]=2*vec[1];
                board[i][2]=0;
                board[i][3]=0;
            }else{
                board[i][0]=vec[0];
                board[i][1]=vec[1];
                board[i][2]=vec[2];
                board[i][3]=0;
            }
        }else if(sz==4){
            if(vec[0]==vec[1]){
                board[i][0]=2*vec[0];
                board[i][1]=vec[2];
                board[i][2]=vec[3];
                board[i][3]=0;
            }else if(vec[1]==vec[2]){
                board[i][0]=vec[0];
                board[i][1]=2*vec[1];
                board[i][2]=vec[3];
                board[i][3]=0;
            }else if(vec[2]==vec[3]){
                board[i][0]=vec[0];
                board[i][1]=vec[1];
                board[i][2]=2*vec[2];
                board[i][3]=0;
            }else{
                board[i][0]=vec[0];
                board[i][1]=vec[1];
                board[i][2]=vec[2];
                board[i][3]=vec[3];
            }
        }
    }
    updateBoard();
}
int Widget::leftCount(int row){
    int cnt=0;
    for(int i=0;i<4;i++){
        if(board[row][i]==0){
            cnt++;
        }else{
            break;
        }
    }
    return cnt;
}
void Widget::rightMerge()
{
    canmove=countEmpty()>0;
    if(!canmove){
        QMessageBox::information(this,QStringLiteral("失败"),QStringLiteral("游戏结束，再接再厉！"));
        return;
    }
    getBoard();
    for(int i=0;i<4;i++){
        int cnt=rightCount(i);
        QList<int> vec;
        for(int j=3-cnt;j>=0;j--){
            if(board[i][j]>=2){
                vec<<board[i][j];
            }
        }
        int sz=vec.size();
        if(sz==0){
            continue;
        }else if(sz==1){
            board[i][3]=vec[0];
            board[i][1]=0;
            board[i][2]=0;
            board[i][0]=0;
        }else if(sz==2){
            if(vec[0]==vec[1]){
                board[i][3]=2*vec[0];
                board[i][2]=0;
            }else{
                board[i][3]=vec[0];
                board[i][2]=vec[1];
            }
            board[i][0]=0;
            board[i][1]=0;
        }else if(sz==3){
            if(vec[0]==vec[1]){
                board[i][3]=2*vec[0];
                board[i][2]=vec[2];
                board[i][1]=0;
                board[i][0]=0;
            }else if(vec[1]==vec[2]){
                board[i][3]=vec[0];
                board[i][2]=2*vec[1];
                board[i][1]=0;
                board[i][0]=0;
            }else{
                board[i][3]=vec[0];
                board[i][2]=vec[1];
                board[i][1]=vec[2];
                board[i][0]=0;
            }
        }else if(sz==4){
            if(vec[0]==vec[1]){
                board[i][3]=2*vec[0];
                board[i][2]=vec[2];
                board[i][1]=vec[3];
                board[i][0]=0;
            }else if(vec[1]==vec[2]){
                board[i][3]=vec[0];
                board[i][2]=2*vec[1];
                board[i][1]=vec[3];
                board[i][0]=0;
            }else if(vec[2]==vec[3]){
                board[i][3]=vec[0];
                board[i][2]=vec[1];
                board[i][1]=2*vec[2];
                board[i][0]=0;
            }else{
                board[i][3]=vec[0];
                board[i][2]=vec[1];
                board[i][1]=vec[2];
                board[i][0]=vec[3];
            }
        }
    }
    updateBoard();
}

int Widget::rightCount(int row)
{
    int cnt=0;
    for(int i=3;i>=0;i--){
        if(board[row][i]==0){
            cnt++;
        }else{
            break;
        }
    }
    return cnt;
}
void Widget::upMerge(){
    canmove=countEmpty()>0;
    if(!canmove){
        QMessageBox::information(this,QStringLiteral("失败"),QStringLiteral("游戏结束，再接再厉！"));
        return;
    }
    getBoard();
    for(int i=0;i<4;i++){
        int cnt=upCount(i);
        QList<int> vec;
        for(int j=cnt;j<4;j++){
            if(board[j][i]>=2){
                vec<<board[j][i];
            }
        }
        int sz=vec.size();
        if(sz==0){
            continue;
        }else if(sz==1){
            board[0][i]=vec[0];
            board[1][i]=0;
            board[2][i]=0;
            board[3][i]=0;
        }else if(sz==2){
            if(vec[0]==vec[1]){
                board[0][i]=2*vec[0];
                board[1][i]=0;
            }else{
                board[0][i]=vec[0];
                board[1][i]=vec[1];
            }
            board[2][i]=0;
            board[3][i]=0;
        }else if(sz==3){
            if(vec[0]==vec[1]){
                board[0][i]=2*vec[0];
                board[1][i]=vec[2];
                board[2][i]=0;
                board[3][i]=0;
            }else if(vec[1]==vec[2]){
                board[0][i]=vec[0];
                board[1][i]=2*vec[1];
                board[2][i]=0;
                board[3][i]=0;
            }else{
                board[0][i]=vec[0];
                board[1][i]=vec[1];
                board[2][i]=vec[2];
                board[3][i]=0;
            }
        }else if(sz==4){
            if(vec[0]==vec[1]){
                board[0][i]=2*vec[0];
                board[1][i]=vec[2];
                board[2][i]=vec[3];
                board[3][i]=0;
            }else if(vec[1]==vec[2]){
                board[0][i]=vec[0];
                board[1][i]=2*vec[1];
                board[2][i]=vec[3];
                board[3][i]=0;
            }else if(vec[2]==vec[3]){
                board[0][i]=vec[0];
                board[1][i]=vec[1];
                board[2][i]=2*vec[2];
                board[3][i]=0;
            }else{
                board[0][i]=vec[0];
                board[1][i]=vec[1];
                board[2][i]=vec[2];
                board[3][i]=vec[3];
            }
        }
    }
    updateBoard();
}

int Widget::upCount(int col)
{
    int cnt=0;
    for(int i=0;i<4;i++){
        if(board[i][col]==0){
            cnt++;
        }else{
            break;
        }
    }
    return cnt;
}
void Widget::downMerge()
{
    canmove=countEmpty()>0;
    if(!canmove){
        QMessageBox::information(this,QStringLiteral("失败"),QStringLiteral("游戏结束，再接再厉！"));
        return;
    }
    getBoard();
    for(int i=0;i<4;i++){
        int cnt=downCount(i);
        QList<int> vec;
        for(int j=3-cnt;j>=0;j--){
            if(board[j][i]>=2){
                vec<<board[j][i];
            }
        }
        int sz=vec.size();
        if(sz==0){
            continue;
        }else if(sz==1){
            board[3][i]=vec[0];
            board[2][i]=0;
            board[1][i]=0;
            board[0][i]=0;
        }else if(sz==2){
            if(vec[0]==vec[1]){
                board[3][i]=2*vec[0];
                board[2][i]=0;
            }else{
                board[3][i]=vec[0];
                board[2][i]=vec[1];
            }
            board[1][i]=0;
            board[0][i]=0;
        }else if(sz==3){
            if(vec[0]==vec[1]){
                board[3][i]=2*vec[0];
                board[2][i]=vec[2];
                board[1][i]=0;
                board[0][i]=0;
            }else if(vec[1]==vec[2]){
                board[3][i]=vec[0];
                board[2][i]=2*vec[1];
                board[1][i]=0;
                board[0][i]=0;
            }else{
                board[3][i]=vec[0];
                board[2][i]=vec[1];
                board[1][i]=vec[2];
                board[0][i]=0;
            }
        }else if(sz==4){
            if(vec[0]==vec[1]){
                board[3][i]=2*vec[0];
                board[2][i]=vec[2];
                board[1][i]=vec[3];
                board[0][i]=0;
            }else if(vec[1]==vec[2]){
                board[3][i]=vec[0];
                board[2][i]=2*vec[1];
                board[1][i]=vec[3];
                board[0][i]=0;
            }else if(vec[2]==vec[3]){
                board[3][i]=vec[0];
                board[2][i]=vec[1];
                board[1][i]=2*vec[2];
                board[0][i]=0;
            }else{
                board[3][i]=vec[0];
                board[2][i]=vec[1];
                board[1][i]=vec[2];
                board[0][i]=vec[3];
            }
        }
    }
    updateBoard();
}
int Widget::downCount(int col)
{
    int cnt=0;
    for(int i=3;i>=0;i--){
        if(board[i][col]==0){
            cnt++;
        }else{
            break;
        }
    }
    return cnt;
}
void Widget::updateBoard(){
    for(int i=0;i<16;i++){
        if(board[i/4][i%4]){
            num[i]->setText(QString::number(board[i/4][i%4]));
             temp[i]=false;
        }else{
            num[i]->setText(QString(""));
             temp[i]=true;
        }
        num[i]->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
        num[i]->setStyleSheet("QLabel{font-size:45px;}");
        QPalette palette;
        int id1=qLn(board[i/4][i%4])/qLn(2);
        if(id1<0) id1=0;
        //qDebug()<<"id1= "<<id1<<endl;
        palette.setColor(QPalette::Background,QColor(colorTab[id1][0],colorTab[id1][1],colorTab[id1][2]));
        num[i]->setAutoFillBackground(true);
        num[i]->setPalette(palette);
    }
}
void Widget::getBoard()
{
    for(int i=0;i<16;i++){
        QString str=num[i]->text();
        board[i/4][i%4]=str.toInt();
    }
}
void Widget::generateNum()
{
    canmove=countEmpty()>0;
    if(!canmove){
        QMessageBox::information(this,QStringLiteral("失败"),QStringLiteral("游戏结束，再接再厉！"));
        return;
    }
    int index,n;
    index=qrand()%16;
    while(!temp[index]){
        index=qrand()%16;
    }
    n=qrand()%2==0?2:4;
    num[index]->setText(QString::number(n));
    num[index]->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    num[index]->setStyleSheet("QLabel{font-size:45px;}");
    QPalette palette;
    int id1=qLn(n)/qLn(2);
    palette.setColor(QPalette::Background,QColor(colorTab[id1][0],colorTab[id1][1],colorTab[id1][2]));
    num[index]->setAutoFillBackground(true);
    num[index]->setPalette(palette);
    temp[index]=false;
}
int Widget::countEmpty(){
    int cnt=0;
    for(int i=0;i<16;i++){
        if(temp[i]){
            cnt++;
        }
    }
    return cnt;
}
void Widget::setScore(){
    QString str=QString::asprintf("得分：%d",this->score);
    ui->lab_score->setText(str);
}
void Widget::updateScore()
{
    getBoard();
    int sum=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==2048){
                QMessageBox::information(this,QStringLiteral("好消息"),QStringLiteral("恭喜完成，太厉害啦！"));
                return;
            }
            sum+=board[i][j];
        }
    }
    ui->lab_score->setText(QString::number(sum));
}
void Widget::Initial()
{
    this->score=0;
    canmove=true;

    setColor();
    setScore();
    setNum();
    startGame();
    //generateNum();

}

void Widget::InitialTest()
{
    this->score=0;
    canmove=true;

    setScore();
    //setNum();
    setNumTset();
    startGame();
    //generateNum();
}
void Widget::setColor(){
    colorTab[0][0]=0xcc;colorTab[0][1]=0xc0;colorTab[0][2]=0xb2;
    colorTab[1][0]=0xee;colorTab[1][1]=0xe4;colorTab[1][2]=0xda;
    colorTab[2][0]=0xec;colorTab[2][1]=0xe0;colorTab[2][2]=0xc8;
    colorTab[3][0]=0xf2;colorTab[3][1]=0xb1;colorTab[3][2]=0x79;
    colorTab[4][0]=0xf5;colorTab[4][1]=0x95;colorTab[4][2]=0x63;
    colorTab[5][0]=0xf5;colorTab[5][1]=0x7c;colorTab[5][2]=0x5f;
    colorTab[6][0]=0xf6;colorTab[6][1]=0x5d;colorTab[6][2]=0x38;
    colorTab[7][0]=0xed;colorTab[7][1]=0xc1;colorTab[7][2]=0x71;
    colorTab[8][0]=0xed;colorTab[8][1]=0xcc;colorTab[8][2]=0x61;
    colorTab[9][0]=0xec;colorTab[9][1]=0xc8;colorTab[9][2]=0x50;
    colorTab[10][0]=0xed;colorTab[10][1]=0xc5;colorTab[10][2]=0x3f;
    colorTab[11][0]=0xef;colorTab[11][1]=0xc4;colorTab[11][2]=0xef;
}
void Widget::on_pbt_restart_clicked()
{
    Initial();
    //InitialTest();
    this->grabKeyboard();
}

void Widget::on_pbt_exit_clicked()
{
    this->destroy();
}
