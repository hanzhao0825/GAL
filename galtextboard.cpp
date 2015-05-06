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
    board = QImage("./res/gal/image/icon/textboard.png");
}

GALTextBoard::~GALTextBoard()
{

}

void GALTextBoard::paint(QPainter &painter) {
    painter.drawImage(0,560,board);
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
    log.push_back(str);
}

bool GALTextBoard::doneDisplay() {
    return pos >= str.size();
}

void GALTextBoard::showAll() {
    pos = str.size();
}
