#include "window.h"

snakewindow::snakewindow(QWidget *parent) :
    QWidget(parent)
{
    fr = new board(this);
    qpbstart = new QPushButton("Start",this);
    qpbhs = new QPushButton("High Scores",this);
    qhb = new QHBoxLayout;
    qvb = new QVBoxLayout;
    l1 = new QLCDNumber(this);
    l2 = new QLCDNumber(this);
    l3 = new QLabel("Level:",this);
    l4 = new QLabel("Score:",this);
    //this->setMaximumSize(640,480);
    this->setMinimumSize(480,250);
    fr->setMinimumSize(201,201);
    //fr->setMaximumSize(201,201);
    qpbstart->setMinimumWidth(100);
    qpbstart->setMaximumWidth(100);
    qpbhs->setMinimumWidth(100);
    qpbhs->setMaximumWidth(100);
    l1->setMinimumWidth(100);
    l1->setMaximumWidth(100);
    l2->setMinimumWidth(100);
    l2->setMaximumWidth(100);
    l3->setMinimumWidth(100);
    l3->setMaximumWidth(100);
    l4->setMinimumWidth(100);
    l4->setMaximumWidth(100);
    qvb->addWidget(qpbstart);
    qvb->addWidget(qpbhs);
    qvb->addWidget(l3);
    qvb->addWidget(l1);
    qvb->addWidget(l4);
    qvb->addWidget(l2);
    qhb->addWidget(fr);
    qhb->addLayout(qvb);
    this->setLayout(qhb);
    connect(qpbstart,SIGNAL(clicked()),fr,SLOT(start()));
    connect(qpbhs,SIGNAL(clicked()),this,SLOT(viewhighscores()));
}

void snakewindow::test(int i,int j){
    l1->display(QString::number(i));
    l2->display(QString::number(j));
}
void snakewindow::end(){
    this->close();
}
void snakewindow::viewhighscores(){
    hs = new highscores();
    hs->show();
}
