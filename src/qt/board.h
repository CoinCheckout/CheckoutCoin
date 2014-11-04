#ifndef BOARD_H
#define BOARD_H

#include<QtGui>
#include<QVector>
#include "save.h"

class board:public QFrame
{
    Q_OBJECT
public:
    board(QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
public slots:
    void movex(int);
    void movey(int);
    void start();
signals:
    void test2(int,int);
    void end();
private:
    bool isStarted,isChanged;
    QBasicTimer timer;
    int timeoutTime() { return 1000 / (3 + 3*level); }
    QVector<int> qvtemp;
    QVector<QVector<int> > qvtail;
    void genfood();
    bool check_snake();
    int x,y,dir,mv,level,length,fx,fy,score,hs,fr,chnglen;
    void end_game();
    void save_score();
    int lowesthighscore();
    QVector<QVector<QString> > qvscores;
};

#endif // BOARD_H
