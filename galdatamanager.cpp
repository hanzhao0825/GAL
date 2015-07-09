#include "galdatamanager.h"

GALDataManager::GALDataManager()
{
    status = "Load";
    refresh();
}

GALDataManager::~GALDataManager()
{

}

void GALDataManager::mouseMove(QMouseEvent *e) {
    if (e->x() < 70 || e->x() > 1010 || e->y() < 100 || e->y() > 550) focus = -1;
    else focus = (e->x()-70>540) * 3 + (e->y()-100) / 150;
}

void GALDataManager::paint(QPainter &painter) {
    painter.setFont(QFont("default", 30, -1, false));
    painter.drawText(0, 40, 1080, 60, Qt::AlignHCenter, status);
    painter.setFont(QFont("default", 15, -1, false));
    for (int i = 0; i < 6; i ++) {
        if (i == focus) {
            painter.drawRect(35+540*((i>2)), 150 * (i%3)+100, 470, 108);
        }
        painter.setOpacity(0.5);
        painter.drawRect(35+540*((i>2)), 150 * (i%3)+100, 470, 108);
        painter.setOpacity(1);
        if (galStatus[i].curDate != "") {
            painter.drawRect(70+540*((i>2)), 150 * (i%3)+100, 162, 108);
            painter.drawPixmap(70+540*((i>2)), 150 * (i%3)+100, galStatus[i].cap);
            painter.drawText(QRect(270+540*((i>2)), 150 * (i%3)+115, 200, 100), galStatus[i].curDate);
            painter.drawText(QRect(270+540*((i>2)), 150 * (i%3)+135, 200, 100), "Chapter " + galStatus[i].fname);
            painter.drawText(QRect(270+540*((i>2)), 150 * (i%3)+155, 200, 100), galStatus[i].lastWords.length() > 20 ? galStatus[i].lastWords.left(20) + "..." :galStatus[i].lastWords );
        } else {
            painter.drawRect(70+540*((i>2)), 150 * (i%3)+100, 162, 108);
            painter.drawText(QRect(270+540*((i>2)), 150 * (i%3)+120, 200, 100), "No Data");
            painter.setOpacity(1);
        }
    }
}

void GALDataManager::refresh() {
    focus = -1;
    for (int i = 0; i < 6; i ++){
        galStatus[i].init();
        galStatus[i].loadFrom(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/data/"+QString::number(i, 10)), 0);
        galStatus[i].charImg.clear();
    }

}
