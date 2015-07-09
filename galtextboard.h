#ifndef GALTEXTBOARD_H
#define GALTEXTBOARD_H

#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <vector>
using namespace std;
class GALTextBoard
{
public:
    GALTextBoard();
    ~GALTextBoard();
    void paint(QPainter &painter, bool skip);
    void update();
    void changeStr(QString str, QString name);
    bool doneDisplay();
    void showAll();
    void setDuration(int d);
    void init();
    vector<QString> log;

private:
    int left, top, width, height;
    int nameLeft, nameTop;
    QString str, name;
    int pos;
    QPixmap board;
    int timeCnt, timeDuration;
};

#endif // GALTEXTBOARD_H
