#include "galscene.h"

GALScene::GALScene() {
    x = 0;
}

GALScene::~GALScene() {

}

void GALScene::paint(QPainter& painter) {
    x += 10;
    painter.setPen(QColor(100,200,100));
    painter.setBrush(QBrush(QColor(100,100,200)));
    painter.drawLine(x, 0, 100, 100);
}
