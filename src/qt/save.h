#ifndef SAVE_H
#define SAVE_H

#include <QtGui>
#include <QVector>
#include<QtAlgorithms>

class save : public QWidget
{
    Q_OBJECT
public:
    save(QWidget *parent=0, int score=0);
    QLabel *ql;
    QLineEdit *le;
    QPushButton *qpb;
    QHBoxLayout *qhb;
private slots:
    void btn_save();
private:
    QVector<QVector<QString> > qvscores;
    QVector<QString> qvtemp;
    int scr,i;
};

#endif // SAVE_H
