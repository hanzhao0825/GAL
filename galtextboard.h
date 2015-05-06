#ifndef GALTEXTBOARD_H
#define GALTEXTBOARD_H

#include <QPainter>
#include <QDebug>
#include <vector>
using namespace std;
class GALTextBoard
{
public:
    GALTextBoard();
    ~GALTextBoard();
    void paint(QPainter &painter);
    void changeStr(QString str, QString name);
    bool doneDisplay();
    void showAll();
    vector<QString> log;

private:
    int left, top, width, height;
    int nameLeft, nameTop;
    QString str, name;
    int pos;
    QImage board;
};

#endif // GALTEXTBOARD_H
