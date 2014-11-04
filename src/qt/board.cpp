
#include "board.h"

board::board(QWidget *parent)
{
    chnglen=10;
    mv=10;
    isStarted=false;
    setFrameStyle(QFrame::Raised | QFrame::StyledPanel);
    setFocusPolicy(Qt::StrongFocus);
    connect(this,SIGNAL(test2(int,int)),parent,SLOT(test(int,int)));
    connect(this,SIGNAL(end()),parent,SLOT(end()));
}
void board::start(){
    this->setFocus();
    isStarted=true;
    isChanged=true;
    x=10;
    y=10;
    length=1;
    level = 1;
    dir=4;
    score=0;
    genfood();
    this->update();
    timer.start(timeoutTime(), this);
}

void board::movex(int i){
    x=i;
    this->update();
}
void board::movey(int j){
    y=-j;
    this->update();
}
void board::paintEvent(QPaintEvent *event){
    QPainter qp(this);
    qp.drawRect(QRect(0,0,200,200));
    if(isStarted==true){
        qp.drawRect(QRect(fx,fy,mv,mv));
        for(int i=0;i<qvtail.size();i++)
            qp.drawRect(QRect(qvtail[i][0],qvtail[i][1],mv,mv));
    }
}
void board::keyPressEvent(QKeyEvent *event){
    if(isChanged==true){
        switch (event->key()) {
        case Qt::Key_Left:
            if(dir!=4)
                dir=1;
            break;
        case Qt::Key_Right:
            if(dir!=1)
                dir=4;
            break;
        case Qt::Key_Down:
            if(dir!=2)
                dir=3;
            break;
        case Qt::Key_Up:
            if(dir!=3)
                dir=2;
            break;
        default:
            QFrame::keyPressEvent(event);
        }
        isChanged=false;
    }
    this->update();
}
void board::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        emit(test2(level,score));
        isChanged=true;
        switch (dir) {
        case 1:
            x-=mv;
            break;
        case 4:
            x+=mv;
            break;
        case 3:
            y+=mv;
            break;
        case 2:
            y-=mv;
            break;
        }
        if(check_snake()){
            end_game();
            return;
        }
        if(x<0)
            x=200-mv;
        if(x>200-mv)
            x=0;
        if(y<0)
            y=200-mv;
        if(y>200-mv)
            y=0;
        if(fx==x && fy==y){
            genfood();
            length++;
            score+=level*10;
            if(length%chnglen==0){
                level++;
                //length=1;
                timer.stop();
                timer.start(timeoutTime(), this);
            }

        }
        this->update();
        qvtemp.clear();
        qvtemp.push_front(y);
        qvtemp.push_front(x);
        qvtail.push_front(qvtemp);
        while(qvtail.size()>length)
            qvtail.pop_back();
    }
    else {
        QFrame::timerEvent(event);
    }
}

void board::genfood(){
    fx=(qrand()%19)*mv;
    fy=(qrand()%19)*mv;
}
void board::end_game(){
    int k=0;
    timer.stop();
    isStarted=false;
    k = lowesthighscore();
    QMessageBox msgBox;
    QPushButton *save;
    if (score>hs || k<10)
        save = msgBox.addButton(tr("&Save Score"), QMessageBox::ActionRole);
    QPushButton *restart = msgBox.addButton(tr("&Restart"), QMessageBox::ActionRole);
    QPushButton *exit = msgBox.addButton(tr("&Exit"), QMessageBox::ActionRole);
    msgBox.setText("You have died!!\nBetter luck next time!!!");
    msgBox.exec();
    if (score>hs || k<10){
        if (msgBox.clickedButton() == save) {
                save_score();
            }
    }
    else if (msgBox.clickedButton() == restart) {
        this->setFocus();
    }
    else if (msgBox.clickedButton() == exit) {
        emit end();
    }
}
bool board::check_snake(){
    for(int i=0;i<qvtail.size();i++)
        if(qvtail[i][0]==x && qvtail[i][1]==y)
            return 1;
    return 0;
}
void board::save_score(){
    save *sv=new save(0,score);
    sv->show();
}
int board::lowesthighscore(){
    QFile fl("test.dat");
    fl.open(QIODevice::ReadOnly);
    QDataStream datas(&fl);
    datas>>qvscores;
    hs=0;
    if(qvscores.size()>0)
        hs=qvscores[qvscores.size()-1][1].toInt();
    fl.close();
    return qvscores.size();
}
