#ifndef GALSELECT_H
#define GALSELECT_H

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QApplication>
#include <QDir>
#include <vector>
using namespace std;

class GALSelect
{
public:
    GALSelect();
    ~GALSelect();

    void change(int cs, vector<QString> &t, vector<QString> &f, vector<int> &v);
    void mouseMove(QMouseEvent *e);
    void paint(QPainter &painter);

    int focus;
    int choiceSum;
    vector<QString> text, fname;
    vector<int> valid;
    QPixmap back;
};

#endif // GALSELECT_H
