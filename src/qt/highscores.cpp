#include "highscores.h"

highscores::highscores()
{
    QFile fl("test.dat");
    fl.open(QIODevice::ReadWrite);
    QDataStream datas(&fl);
    qltext = new QLabel("<b>Name</b><br>",this);
    qlscore = new QLabel("<b>Score</b><br>",this);
    qhb = new QHBoxLayout;
    datas>>qvscores;
    for(int i=0;i<qvscores.size();i++){
        qltext->setText(qltext->text()+"<br>"+qvscores[i][0]);
        qlscore->setText(qlscore->text()+"<br>"+qvscores[i][1]);
    }
    qhb->addWidget(qltext);
    qhb->addWidget(qlscore);
    this->setLayout(qhb);
    fl.close();
}
