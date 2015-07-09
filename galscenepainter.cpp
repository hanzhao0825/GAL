#include "galscenepainter.h"

GALScenePainter::GALScenePainter()
{

}

GALScenePainter::~GALScenePainter()
{

}

void GALScenePainter::paint(QPainter &painter, int left, int top, GALStatus &galStatus) {
    if (galStatus.scene.size() == QSize(0, 0)) {
        galStatus.scene.load(QDir::toNativeSeparators(":/res/gal/image/scene/"+galStatus.curScene+".png"));
    }
    painter.drawPixmap(left, top, 1080, 720, galStatus.scene);

    for (auto it = galStatus.curChar.begin(); it != galStatus.curChar.end(); ++it) {

        double charScale = galStatus.galCharAnimator.charScale[it->first] == 0? 1 : galStatus.galCharAnimator.charScale[it->first];
        int charLeft = it->second.second-(620.0)*charScale;
        int charScaleD = galStatus.galCharAnimator.charScale[it->first] == 0? 0 : (galStatus.galCharAnimator.charScale[it->first]-1) * 150;
        int charTop = galStatus.galCharAnimator.charBase[it->first]-galStatus.galCharAnimator.curY[it->first]-charScaleD ;


        int rcleft = left + charLeft + galStatus.charPos[it->first][make_pair(it->first,it->first)].first;
        int rcTop = top + charTop + galStatus.charPos[it->first][make_pair(it->first,it->first)].second;

        painter.drawPixmap(rcleft, rcTop, galStatus.charImg[it->first][make_pair(it->first,it->first)]);
        for (auto it2 = it->second.first.begin(); it2 != it->second.first.end(); ++ it2) {
            if (it2->second == "X") continue;
            int rLeft = left + charLeft+galStatus.charPos[it->first][make_pair(it2->first,it2->second)].first;
            int rTop = top + charTop+galStatus.charPos[it->first][make_pair(it2->first,it2->second)].second;
            painter.drawPixmap(rLeft, rTop, galStatus.charImg[it->first][make_pair(it2->first,it2->second)]);
        }
    }
    if (galStatus.curMask != "" && galStatus.curMask != "X") {
        if (galStatus.mask.size() == QSize(0, 0)) {
            galStatus.mask = QPixmap(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/res/gal/image/mask/"+galStatus.curMask+".png"));
        }
        painter.drawPixmap(left, top, 1080, 720, galStatus.mask);
    }
    if (galStatus.curChanger != "" && galStatus.curChanger != "X" && galStatus.galSceneChanger.status != "X") {

        if (galStatus.curChanger == "BLACK") {
            galStatus.changer = QPixmap(QSize(1080, 720));
            if (galStatus.galSceneChanger.status == "PRE") galStatus.changer.fill(QColor(0, 0, 0, 255 - galStatus.galSceneChanger.duration));
            if (galStatus.galSceneChanger.status == "POST") galStatus.changer.fill(QColor(0, 0, 0, galStatus.galSceneChanger.duration));
        }
        painter.drawPixmap(left, top, 1080, 720, galStatus.changer);
    }
}
