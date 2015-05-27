#include "galscenepainter.h"

GALScenePainter::GALScenePainter()
{

}

GALScenePainter::~GALScenePainter()
{

}

void GALScenePainter::paint(QPainter &painter, int left, int top, double scale, GALStatus &galStatus) {
    QImage tImg(QSize(1080*scale, 720*scale), QImage::Format_ARGB32);
    tImg.fill(0x00000000);
    QPainter tPainter(&tImg);
    if (galStatus.scene == QImage(NULL)) {
        tImg.fill(0x00000000);
        galStatus.scene = QImage(QDir::toNativeSeparators(QDir::currentPath()+"/res/gal/image/scene/"+galStatus.curScene+".png"));
    }
    tPainter.drawImage(QRectF(0, 0, 1080*scale, 720*scale), galStatus.scene);

    for (auto it = galStatus.curChar.begin(); it != galStatus.curChar.end(); ++it) {
        if (galStatus.charImg[it->first] == QImage(NULL)) {
            QImage cImg = QImage(QSize(1240, 1754), QImage::Format_ARGB32);
            cImg.fill(0x00000000);
            QPainter charPainter(&cImg);
            charPainter.drawImage(0, 0, QImage(QDir::toNativeSeparators(QDir::currentPath()+"/res/gal/image/character/"+it->first+"/"+it->first+".png")));
            for (auto it2 = it->second.first.begin(); it2 != it->second.first.end(); ++ it2) {
                if (it2->second == "X") continue;
                charPainter.drawImage(0, 0, QImage(QDir::toNativeSeparators(QDir::currentPath()+"/res/gal/image/character/"+it->first+"/"+it2->first+"/"+it2->second+".png")));
            }
            galStatus.charImg[it->first] = cImg;
        }
        QImage img = galStatus.charImg[it->first];
        double charScale = galStatus.galCharAnimator.charScale[it->first] == 0? 1 : galStatus.galCharAnimator.charScale[it->first];
        int charLeft = (it->second.second-(img.width()/2)*charScale)*scale;
        int charScaleD = galStatus.galCharAnimator.charScale[it->first] == 0? 0 : (galStatus.galCharAnimator.charScale[it->first]-1) * 150;
        int charTop = (galStatus.galCharAnimator.charBase[it->first]-galStatus.galCharAnimator.curY[it->first]-charScaleD)*scale ;

        tPainter.drawImage(QRectF(charLeft, charTop, img.width()*scale*charScale, img.height()*scale*charScale), img);
    }
    if (galStatus.curMask != "" && galStatus.curMask != "X") {
        if (galStatus.mask == QImage(NULL)) {
            galStatus.mask = QImage(QDir::toNativeSeparators(QDir::currentPath()+"/res/gal/image/mask/"+galStatus.curMask+".png"));
        }
        tPainter.drawImage(QRectF(0, 0, 1080*scale, 720*scale), galStatus.mask);
    }
    if (galStatus.curChanger != "" && galStatus.curChanger != "X" && galStatus.galSceneChanger.status != "X") {

        if (galStatus.curChanger == "BLACK") {
            galStatus.changer = QImage(QSize(1080*scale, 720*scale), QImage::Format_ARGB32);
            if (galStatus.galSceneChanger.status == "PRE") galStatus.changer.fill(qRgba(0, 0, 0, 255 - galStatus.galSceneChanger.duration));
            if (galStatus.galSceneChanger.status == "POST") galStatus.changer.fill(qRgba(0, 0, 0, galStatus.galSceneChanger.duration));
        }
        tPainter.drawImage(QRectF(0, 0, 1080*scale, 720*scale), galStatus.changer);
    }
    painter.drawImage(QRectF(left, top, 1080.0*scale, 720.0*scale), tImg);

}
