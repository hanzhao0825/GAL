#include "galscenepainter.h"

GALScenePainter::GALScenePainter()
{

}

GALScenePainter::~GALScenePainter()
{

}

void GALScenePainter::paint(QPainter &painter, int left, int top, double scale, GALStatus &galStatus, map<QString, QImage> &charImg, QImage &scene) {
    if (scene == QImage(NULL)) {
        scene = QImage("./res/gal/image/scene/"+galStatus.curScene+".png");
    }
    painter.drawImage(QRectF(left, top, 1080*scale, 720*scale), scene);
    for (auto it = galStatus.curChar.begin(); it != galStatus.curChar.end(); ++it) {
        if (charImg[it->first] == QImage(NULL)) {
            charImg[it->first] = QImage("./res/gal/image/character/"+it->first+"_"+it->second.first+".png");
        }
        QImage img = charImg[it->first];
        painter.drawImage(QRectF(left+(it->second.second-img.width()/2)*scale, top+(720-img.height())*scale, img.width()*scale, img.height()*scale), img);
    }
}
