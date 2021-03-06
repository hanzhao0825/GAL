#include "galscene.h"

GALScene::GALScene() {
    charPos["MID"] = 540;
    charPos["LEFT"] = 320;
    charPos["RIGHT"] = 760;
    MUSTWAIT = 0;
    curPath = QApplication::applicationDirPath();
    voice = new QSound("");
    state = "GALSCENE";
    frameCnt = 0;

}

GALScene::~GALScene() {
}

void GALScene::paint(QPainter& painter) {
#ifdef Q_OS_MAC
    painter.setFont(QFont("default", 23, -1, false));
#else
    painter.setFont(QFont("微软雅黑", 20, -1, false));
#endif
    painter.setPen(QColor(255,255,255));
    galScenePainter.paint(painter, galSceneShaker.curX, galSceneShaker.curY, galStatus);
    if (state != "CG") {
        galTextBoard.paint(painter, galSkipper.skip);
        galBottomBar.paint(painter);
    }
    if (state == "LOAD" || state == "SAVE")
        galDataManager.paint(painter);
    if (state == "SELECT")
        galSelect.paint(painter);
}

void GALScene::mousePress(QMouseEvent *e) {
    if (MUSTWAIT) return;
    if (state == "GALSCENE") {
        if (e->button() == Qt::RightButton) {
            state = "CG";
            return;
        }
        if (galBottomBar.focus != -1) {
            switch (galBottomBar.focus) {
                case 0:
                    state = "LOAD";
                    galDataManager.status = "LOAD";
                    galDataManager.refresh();
                    break;
                case 1:
                    state = "SAVE";
                    galDataManager.status = "SAVE";
                    galDataManager.refresh();
                    break;
                case 2:
                    galSkipper.skip = !galSkipper.skip;
            }
            return;
        }
        if (!galTextBoard.doneDisplay()) {
            galTextBoard.showAll();
            return;
        }
        nextActions();
    } else if (state == "LOAD" || state == "SAVE") {
        if (galDataManager.focus == -1) {
            state = "GALSCENE";
        } else {
            QString fname = QDir::toNativeSeparators(QApplication::applicationDirPath()+"/data/"+QString::number(galDataManager.focus, 10));
            if (state == "LOAD") {
                galStatus.init();
                galStatus.loadFrom(fname, &galCharLoaderManager);
                loadFrom(galStatus.fname, galStatus.lineNum);
            } else if (state == "SAVE") {
                galStatus.saveTo(fname);
            }
            galDataManager.refresh();
        }
    } else if (state == "SELECT") {
        if (galSelect.focus == -1) return;
        state = "GALSCENE";
        jumpToScript(galSelect.fname[galSelect.focus]);
    } else if (state == "CG") {
        state = "GALSCENE";
    }
}

void GALScene::mouseMove(QMouseEvent *e) {
    galBottomBar.mouseMove(e);
    galDataManager.mouseMove(e);
    galSelect.mouseMove(e);
}

void GALScene::jumpToScript(QString fname) {
    galTextBoard.init();
    //galStatus.init();
    galStatus.fname = fname;
    galStatus.lineNum = 0;
    file.close();
    file.setFileName(QDir::toNativeSeparators(curPath+"/res/gal/script/"+fname+".txt"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    nextActions();
}

void GALScene::loadFrom(QString fname, int lineNum) {
    galTextBoard.init();
    galBGM.stop();
    if (galStatus.curBGM != "") galBGM.play(galStatus.curBGM, curPath);
    galStatus.fname = fname;
    galStatus.lineNum = lineNum;
    file.close();
    file.setFileName(QDir::toNativeSeparators(curPath+"/res/gal/script/"+fname+".txt"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray line;
    for (int i = 0; i < lineNum - 1; i ++) {
        line = file.readLine();
    }
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
        if (galStatus.lineNum > galSkipper.lines[galStatus.fname]) {
            galSkipper.skip = false;
            galSkipper.lines[galStatus.fname] = galStatus.lineNum;
            galSkipper.save();
        }
        galStatus.lineNum ++;
        if (strList[0] == "TEXT") {
            if (strList[1] == "X") {
                QString qs = "";
                for (int i = 2; i < strList.length(); i ++)
                    qs += strList[i]+" ";
                galTextBoard.changeStr(qs, "");
                galStatus.lastWords = qs;
            } else {
                QString qs = "";
                for (int i = 3; i < strList.length(); i ++)
                    qs += strList[i]+" ";
                galTextBoard.changeStr(qs, strList[1]);
                galStatus.lastWords = qs;
                if (strList[2] != "X") {
                    galVoice.play(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/res/GAL/voice/"+galStatus.fname+"/"+strList[2]+".wav"));
                }
            }
            break;
        } else if (strList[0] == "SCENE") {
            if (galSkipper.skip || strList[2] == "X") {
                galStatus.curScene = strList[1];
                galStatus.scene = QPixmap(0, 0);
            } else {
                galStatus.nextScene = strList[1];
                galStatus.curChanger = strList[2];
                galStatus.galSceneChanger.status = "PRE";
                galStatus.galSceneChanger.duration = 255;
                galStatus.changer = QPixmap(0, 0);
                break;
            }
        } else if (strList[0] == "CHAR") {
            if (strList[1] == "SHOW") {
                int pos = charPos[strList[3]];
                map<QString, QString> args = galStatus.curChar[strList[2]].first;
                for (int i = 4; i < strList.size(); i ++) {
                    QStringList argsList = strList[i].split("=");
                    args[argsList[0]] = argsList[1];
                }
                galStatus.curChar[strList[2]] = make_pair(args, pos);
            } else if (strList[1] == "REMOVE") {
                galStatus.curChar.erase(strList[2]);
            } else if (strList[1] == "JUMP") {
                if (galSkipper.skip) return;
                galStatus.galCharAnimator.duration[strList[2]] = strList[5].split("=")[1].toInt();
                galStatus.galCharAnimator.curDuration[strList[2]] = strList[5].split("=")[1].toInt();
                galStatus.galCharAnimator.type[strList[2]] = strList[1];
                galStatus.galCharAnimator.jumpLevel[strList[2]] = strList[3].split("=")[1].toInt();
                galStatus.galCharAnimator.jumpTimes[strList[2]] = strList[4].split("=")[1].toInt();
            } else if (strList[1] == "SCALE") {
                galStatus.galCharAnimator.charScale[strList[2]] = strList[3].toDouble();
            } else if (strList[1] == "LOAD") {
                galCharLoaderManager.load(strList[2], &galStatus.charImg[strList[2]], &galStatus.charPos[strList[2]]);
            } else if (strList[1] == "FREE") {
                galStatus.charImg[strList[2]].clear();
            }
        } else if (strList[0] == "BGM") {
            if (strList[1] == "START") {
                galStatus.curBGM = strList[2];
                galBGM.play(galStatus.curBGM, curPath);
            } else if (strList[1] == "STOP") {
                galBGM.stop();
            }
        } else if (strList[0] == "GOTO") {
            jumpToScript(strList[1]);
            break;
        } else if (strList[0] == "SELECT") {
            int cs = strList[1].toInt();
            vector<QString> t, f;
            vector<int> v;
            for (int i = 2; i < 2 + cs; i ++) t.push_back(strList[i]);
            for (int i = 2+cs; i < 2 + cs+cs; i ++) f.push_back(strList[i]);
            for (int i = 2+cs+cs; i < 2 + cs+cs+cs; i ++) v.push_back(strList[i].toInt());
            galSelect.change(cs, t, f, v);
            state = "SELECT";
            galSkipper.skip = false;
            break;
        } else if (strList[0] == "SCENESHAKE") {
            if (galSkipper.skip) return;
            galSceneShaker.maxX = strList[1].split("=")[1].toInt();
            galSceneShaker.maxY = strList[2].split("=")[1].toInt();
            galSceneShaker.duration = strList[3].split("=")[1].toInt();
        } else if (strList[0] == "MASK") {
            galStatus.curMask = strList[1];
        } else if (strList[0] == "TEXTDURATION") {
            galTextBoard.setDuration(strList[1].toInt());
        } else if (strList[0] == "EXIT") {
            exit(0);
        }
    }
}

void GALScene::keyPress(QKeyEvent *keyevent) {
    int uKey = keyevent->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);
    if (key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt ) {
        return ;
    }
    if (!galTextBoard.doneDisplay()) {
        galTextBoard.showAll();
        return;
    }
    nextActions();
}

void GALScene::update() {
    frameCnt ++;
    galStatus.update();
    galTextBoard.update();

    if (galSkipper.skip) {
        if (frameCnt % 5 == 0) nextActions();
        return;
    }
    if (galSceneShaker.duration > 0) {
        galSceneShaker.update(MUSTWAIT);
    }
    if (galStatus.galSceneChanger.duration == 0) {
        if (galStatus.galSceneChanger.status == "PRE") {
            galStatus.galSceneChanger.status = "POST";
            galStatus.galSceneChanger.duration = 255;
            galStatus.curScene = galStatus.nextScene;
            galStatus.scene = QPixmap(0, 0);
        } else if (galStatus.galSceneChanger.status == "POST") {
            galStatus.galSceneChanger.status = "X";
            nextActions();
        }
    }
}
