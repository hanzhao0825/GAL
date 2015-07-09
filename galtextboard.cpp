#include "galtextboard.h"

GALTextBoard::GALTextBoard()
{
    left = 100;
    top = 630;
    width = 880;
    height = 200;
    nameLeft = 100;
    nameTop = 600;
    board = QPixmap(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/res/gal/image/icon/textboard.png"));

    init();
}

GALTextBoard::~GALTextBoard()
{

}

void GALTextBoard::init() {
    str = "";
    name = "";
    pos = 0;
    timeDuration = 1;
}

void GALTextBoard::paint(QPainter &painter, bool skip) {
    painter.drawPixmap(0,560,board);
    if (name != "")
        painter.drawText(QRect(nameLeft, nameTop, width, height), "["+name+"]");
    painter.drawText(QRect(left, top-(name=="")*20, width, height), skip == false ? str.left(pos) : str);
    pos += (timeCnt%timeDuration == 0) ? 1 : 0;
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

void GALTextBoard::update() {
    timeCnt ++;
}

void GALTextBoard::setDuration(int d) {
    timeDuration = d;
}
