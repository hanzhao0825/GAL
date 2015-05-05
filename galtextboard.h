#ifndef GALTEXTBOARD_H
#define GALTEXTBOARD_H

#include <QPainter>
#include <QDebug>

class GALTextBoard
{
public:
    GALTextBoard();
    ~GALTextBoard();
    void paint(QPainter &painter);
    void changeStr(QString str, QString name);
    bool doneDisplay();
    void showAll();

private:
    int left, top, width, height;
    int nameLeft, nameTop;
    QString str, name;
    int pos;
};

#endif // GALTEXTBOARD_H
