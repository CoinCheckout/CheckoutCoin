#include<QApplication>
#include"window.h"

int main(int argc,char **argv){
    QApplication app(argc,argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    window win;
    win.show();
    return app.exec();
}
