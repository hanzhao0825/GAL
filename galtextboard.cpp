#include "galtextboard.h"

GALTextBoard::GALTextBoard()
{
    left = 100;
    top = 630;
    width = 880;
    height = 200;
    nameLeft = 100;
    nameTop = 600;
    str = "";
    name = "";
    pos = 0;
}

GALTextBoard::~GALTextBoard()
{

}

void GALTextBoard::paint(QPainter &painter) {
    painter.drawImage(0,560,QImage("./res/gal/image/icon/textboard.png"));
    if (name != "")
        painter.drawText(QRect(nameLeft, nameTop, width, height), "【"+name+"】");
    painter.drawText(QRect(left, top-(name=="")*20, width, height), str.left(pos++));
    if (pos > str.size())
        pos = str.size();
}

void GALTextBoard::changeStr(QString str, QString name) {
    this->str = str;
    this->name = name;
    pos = 0;
}

bool GALTextBoard::doneDisplay() {
    return pos >= str.size();
}

void GALTextBoard::showAll() {
    pos = str.size();
}
