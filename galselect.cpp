#include "galselect.h"

GALSelect::GALSelect() {
    back = QImage(QDir::toNativeSeparators(QDir::currentPath()+"/res/gal/image/icon/select.png"));
}



GALSelect::~GALSelect()
{

}

void GALSelect::change(int cs, vector<QString> &t, vector<QString> &f, vector<int> &v)
{
    choiceSum = cs;
    text = t;
    fname = f;
    valid = v;
    focus = -1;
}

void GALSelect::paint(QPainter &painter) {
     for (int i = 0; i < choiceSum; i ++) {
         int y = 200 + i * 100;
         painter.drawImage(240, y-35, back);
         if (focus == i) {
             painter.setPen(QColor(255,255,155));
             painter.drawText(0, y, 1080, 100, Qt::AlignHCenter, text[i]);
         } else {
             painter.setPen(QColor(255,255,255));
             painter.drawText(0, y, 1080, 100, Qt::AlignHCenter, text[i]);
         }
     }
}

void GALSelect::mouseMove(QMouseEvent *e) {
    focus = -1;
    if (e->y() < 200 || e->y() > 200 + choiceSum * 100) return;
    focus = (e->y() - 200) / 100;
}
