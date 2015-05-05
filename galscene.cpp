#include "galscene.h"

GALScene::GALScene() {
    charPos["MID"] = 540;
    charPos["LEFT"] = 360;
    charPos["RIGHT"] = 720;
    MUSTWAIT = 0;
    curPath = QApplication::applicationDirPath();
    voice = new QSound("");
}

GALScene::~GALScene() {

}

void GALScene::paint(QPainter& painter) {
    painter.setFont(QFont("default", 23, -1, false));
    painter.setPen(QColor(255,255,255));
    QImage imgScene("./res/gal/image/scene/"+galStatus.curScene+".png");
    painter.drawImage(0,0,imgScene);
    for (auto it = galStatus.curChar.begin(); it != galStatus.curChar.end(); ++it) {
        QImage img("./res/gal/image/character/"+it->first+"_"+it->second.first+".png");
        painter.drawImage(it->second.second-img.width()/2, 720-img.height(), img);
    }
    galTextBoard.paint(painter);
}

void GALScene::mousePress(QMouseEvent *e) {
    if (MUSTWAIT) return;
    if (!galTextBoard.doneDisplay()) {
        galTextBoard.showAll();
        return;
    }
    nextActions();
}

void GALScene::jumpToScript(QString fname) {
    galStatus.fname = fname;
    galStatus.lineNum = 0;
    galStatus.curChar.clear();
    file.close();
    file.setFileName(curPath+"/res/gal/script/"+fname+".txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    nextActions();
}

void GALScene::jumpToScript(QString fname, int lineNum) {
    qDebug() << fname << lineNum;
    galStatus.fname = fname;
    galStatus.lineNum = lineNum;
    file.close();
    file.setFileName(curPath+"/res/gal/script/"+fname+".txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray line;
    for (int i = 0; i < lineNum - 1; i ++)
        line = file.readLine();
    nextActions();
}

QStringList GALScene::getAnotherLine() {
    QString str;
    QByteArray line;
    do{
        line = file.readLine();
        str = QString(line);
        str = str.simplified();
    } while (str=="");
    return str.split(" ");
}

void GALScene::nextActions() {
    while (1) {
        QStringList strList = getAnotherLine();
        qDebug() << strList;
        galStatus.lineNum ++;
        if (strList[0] == "TEXT") {
            if (strList[1] == "X") {
                galTextBoard.changeStr(strList[2], "");
            } else  {
                galTextBoard.changeStr(strList[2], strList[1]);
                if (strList[3] != "X") {
                    delete voice;
                    voice = new QSound("./res/GAL/voice/"+galStatus.fname+"/"+strList[3]+".wav");
                    voice->play();
                }
            }
            break;
        } else if (strList[0] == "SCENE") {
            galStatus.curScene = strList[1];
        } else if (strList[0] == "CHAR") {
            if (strList[1] == "SHOW") {
                galStatus.curChar[strList[2]] = pair<QString, int>(strList[3], charPos[strList[4]]);
            }
            if (strList[1] == "REMOVE") {
                galStatus.curChar.erase(strList[2]);
            }
        } else if (strList[0] == "BGM") {
            if (strList[1] == "START") {
                galStatus.curBGM = curPath+"/res/GAL/bgm/"+strList[2];
                galBGM.play(galStatus.curBGM);
            }
        } else if (strList[0] == "GOTO") {
            jumpToScript(strList[1]);
            break;
        }
    }
}

void GALScene::keyPress(QKeyEvent *keyevent) {
    int uKey = keyevent->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);
    if (key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt ) {
        return ;
    }
    //获取修饰键(Ctrl,Alt,Shift)的状态
    Qt::KeyboardModifiers modifiers = keyevent->modifiers();
    //判断某个修饰键是否被按下
    if(modifiers & Qt::ShiftModifier)
        uKey += Qt::SHIFT;
    if(modifiers & Qt::ControlModifier)
        uKey += Qt::CTRL;
    if(modifiers & Qt::AltModifier)
        uKey += Qt::ALT;
    //popup information
    QString nativeText = QKeySequence(uKey).toString(QKeySequence::NativeText);
    if (nativeText == "F1") {
        saveTo("1");
    }
    if (nativeText == "1") {
        loadFrom("1");
    }
}

void GALScene::saveTo(QString fname) {
    qDebug() << "Saving To " << fname;
    QFile f(fname);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream fout(&f);
    fout << galStatus.curChar.size() << endl;
    for (auto it = galStatus.curChar.begin(); it != galStatus.curChar.end(); ++ it) {
        fout << it->first << " " << it->second.first << " " << it->second.second;
    }
    fout << galStatus.curScene << endl;
    fout << galStatus.curBGM << endl;
    fout << galStatus.fname << endl;
    fout << galStatus.lineNum << endl;
    f.close();
}

void GALScene::loadFrom(QString fname) {
    QFile f(fname);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fin(&f);
    QString lineStr;
    int mapSize;
    fin >> mapSize;
    galStatus.curChar.clear();
    for (int i = 0; i < mapSize; ++ i) {
        QString s1, s2;
        int i3;
        fin >> s1 >> s2 >> i3;
        galStatus.curChar[s1] = make_pair(s2, i3);
    }
    fin >> galStatus.curScene;
    fin >> galStatus.curBGM;
    fin >> galStatus.fname;
    fin >> galStatus.lineNum;
    f.close();
    galBGM.play(galStatus.curBGM);
    jumpToScript(galStatus.fname, galStatus.lineNum);
}

