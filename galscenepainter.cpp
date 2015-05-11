#include "galscenepainter.h"

GALScenePainter::GALScenePainter()
{

}

GALScenePainter::~GALScenePainter()
{

}

void GALScenePainter::paint(QPainter &painter, int left, int top, double scale, GALStatus &galStatus, map<QString, QImage> &charImg, QImage &scene) {
    QImage tImg(QSize(1080*scale, 720*scale), QImage::Format_ARGB32);
    tImg.fill(0x00000000);
    QPainter tPainter(&tImg);
    if (scene == QImage(NULL)) {
        scene = QImage("./res/gal/image/scene/"+galStatus.curScene+".png");
    }
    tPainter.drawImage(QRectF(0, 0, 1080*scale, 720*scale), scene);
    for (auto it = galStatus.curChar.begin(); it != galStatus.curChar.end(); ++it) {
        if (charImg[it->first] == QImage(NULL)) {
            QImage cImg = QImage(QSize(1240, 1754), QImage::Format_ARGB32);
            cImg.fill(0x00000000);
            QPainter charPainter(&cImg);
            charPainter.drawImage(0, 0, QImage("./res/gal/image/character/"+it->first+"/"+it->first+".png"));
            for (auto it2 = it->second.first.begin(); it2 != it->second.first.end(); ++ it2) {
                if (it2->second == "X") continue;
                charPainter.drawImage(0, 0, QImage("./res/gal/image/character/"+it->first+"/"+it2->first+"/"+it2->second+".png"));
            }
            charImg[it->first] = cImg;
        }
        QImage img = charImg[it->first];
        double charScale = galStatus.galCharAnimator.charScale[it->first] == 0? 1 : galStatus.galCharAnimator.charScale[it->first];
        int charLeft = (it->second.second-(img.width()/2)*charScale)*scale;
        int charScaleD = galStatus.galCharAnimator.charScale[it->first] == 0? 0 : (galStatus.galCharAnimator.charScale[it->first]-1) * 150;
        int charTop = (galStatus.galCharAnimator.charBase[it->first]-galStatus.galCharAnimator.curY[it->first]-charScaleD)*scale ;

        tPainter.drawImage(QRectF(charLeft, charTop, img.width()*scale*charScale, img.height()*scale*charScale), img);
    }
    painter.drawImage(QRectF(left, top, 1080*scale, 720*scale), tImg);

}
