#include "galcharanimator.h"

GALCharAnimator::GALCharAnimator()
{
    QFile f(QDir::toNativeSeparators(QDir::currentPath()+"/res/gal/others/charBase"));
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "GALCharAnimator::GALCharAnimator() - Cannot open file";
        return;
    }
    QTextStream fin(&f);
    int mapSize;
    fin >> mapSize;
    charBase.clear();
    for (int i = 0; i < mapSize; ++ i) {
        QString s1;
        int i3;
        fin >> s1 >> i3;
        charBase[s1] = i3;
    }
    f.close();
}

GALCharAnimator::~GALCharAnimator()
{

}

void GALCharAnimator::update() {
    for (auto it = duration.begin(); it != duration.end(); it ++) {
        if (it->second == 0) continue;
        curDuration[it->first] --;
        if (curDuration[it->first] == 0) {
            curY[it->first] = 0;
            it->second = 0;
            continue;
        }
        if (type[it->first] == "JUMP") {
            curY[it->first] = jumpLevel[it->first] * fabs(sin(3.14159 * jumpTimes[it->first] * curDuration[it->first] / it->second));
        }
    }
}
