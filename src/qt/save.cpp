#include "save.h"

save::save(QWidget *parent, int score)
{
    scr=score;
    ql=new QLabel("Enter Name: ",this);
    le=new QLineEdit(this);
    qpb=new QPushButton("Save",this);
    qhb = new QHBoxLayout();
    qhb->addWidget(ql);
    qhb->addWidget(le);
    qhb->addWidget(qpb);
    this->setLayout(qhb);
    connect(qpb,SIGNAL(clicked()),this,SLOT(btn_save()));
}
void save::btn_save(){
    QFile fl("test.dat");
    fl.open(QIODevice::ReadWrite);
    QDataStream qddata(&fl);
    qddata>>qvscores;
    qvtemp.push_back(le->text());
    qvtemp.push_back(QString::number(scr));
    for(i=0;i<qvscores.size();i++)
        if(qvscores[i][1]<qvtemp[1])
            break;
    qvscores.insert(i,qvtemp);
    while(qvscores.size()>10)
        qvscores.pop_back();
    fl.close();
    fl.open(QIODevice::WriteOnly);
    qddata.setDevice(&fl);
    qddata<<qvscores;
    fl.close();
    QMessageBox::information(this,"Save","Your NAME is in the hall of FAME!!","&Ok");
    this->close();
}

