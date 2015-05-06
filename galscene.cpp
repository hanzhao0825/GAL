#include "galscene.h"

GALScene::GALScene() {
    charPos["MID"] = 540;
    charPos["LEFT"] = 360;
    charPos["RIGHT"] = 720;
    MUSTWAIT = 0;
    curPath = QApplication::applicationDirPath();
    voice = new QSound("");
    state = "GalScene";
}

GALScene::~GALScene() {
}

void GALScene::paint(QPainter& painter) {
    painter.setFont(QFont("default", 23, -1, false));
    painter.setPen(QColor(255,255,255));
    galScenePainter.paint(painter, 0, 0, 1, galStatus, charImg, scene);
    galTextBoard.paint(painter);
    galBottomBar.paint(painter);
    if (state == "Load" || state == "Save")
        galDataManager.paint(painter);
}

void GALScene::mousePress(QMouseEvent *e) {
    qDebug() << "mousePress";
    if (MUSTWAIT) return;
    if (state == "GalScene") {
        if (galBottomBar.focus != -1) {
            switch (galBottomBar.focus) {
                case 0:
                    state = "Load";
                    galDataManager.status = "Load";
                    galDataManager.refresh();
                    break;
                case 1:
                    state = "Save";
                    galDataManager.status = "Save";
                    galDataManager.refresh();
                    break;
            }
            return;
        }
        if (!galTextBoard.doneDisplay()) {
            galTextBoard.showAll();
            return;
        }
        nextActions();
    } else if (state == "Load" || state == "Save") {
        if (galDataManager.focus == -1) {
            state = "GalScene";
        } else {
            QString fname = "./data/"+QString::number(galDataManager.focus, 10);
            if (state == "Load") {
                galStatus.loadFrom(fname);
                jumpToScript(galStatus.fname, galStatus.lineNum);
            } else if (state == "Save") {
                galStatus.saveTo(fname);
            }
            galDataManager.refresh();
        }
    }
}

void GALScene::mouseMove(QMouseEvent *e) {
    galBottomBar.mouseMove(e);
    galDataManager.mouseMove(e);
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
    charImg.clear();
    scene = QImage(NULL);
    galBGM.play(curPath+"/res/GAL/bgm/"+galStatus.curBGM);
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
            galStatus.lastWords = strList[2];
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
            scene = QImage("./res/gal/image/scene/"+strList[1]+".png");
        } else if (strList[0] == "CHAR") {
            if (strList[1] == "SHOW") {
                galStatus.curChar[strList[2]] = pair<QString, int>(strList[3], charPos[strList[4]]);
                charImg[strList[2]] = QImage("./res/gal/image/character/"+strList[2]+"_"+strList[3]+".png");
            }
            if (strList[1] == "REMOVE") {
                galStatus.curChar.erase(strList[2]);
            }
        } else if (strList[0] == "BGM") {
            if (strList[1] == "START") {
                galStatus.curBGM = strList[2];
                galBGM.play(curPath+"/res/GAL/bgm/"+galStatus.curBGM);
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
    galStatus.saveTo(fname);
}

void GALScene::loadFrom(QString fname) {
    galStatus.loadFrom(fname);
    jumpToScript(galStatus.fname, galStatus.lineNum);
}

