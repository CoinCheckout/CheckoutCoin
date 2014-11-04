#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include<QtGui>
#include "board.h"
#include "highscores.h"

class snakewindow:public QWidget
{
    Q_OBJECT
public:
    explicit snakewindow(QWidget *parent=0);
    board *fr;
    QHBoxLayout *qhb;
    QVBoxLayout *qvb;
    QPushButton *qpbstart,*qpbhs;
    QLabel *l3,*l4;
    QLCDNumber *l1,*l2;
    highscores *hs;
    int fr1;
public slots:
    void test(int,int);
    void end();
    void viewhighscores();   
};

#endif // SNAKEWINDOW_H
