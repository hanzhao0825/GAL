#include "galstatus.h"

GALStatus::GALStatus()
{
    init();
}

GALStatus::~GALStatus()
{

}

void GALStatus::init() {
    fname = "";
    lineNum = 0;
    curDate = "";
    curScene = "";
    scene = QImage(NULL);
    curChar.clear();
    charImg.clear();
    curBGM = "";
    curMask = "X";
    mask = QImage(NULL);
    curChanger = "X";
    changer = QImage(NULL);
}

void GALStatus::saveTo(QString fname) {
    QFile f(fname);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream fout(&f);
    QDateTime current_date_time = QDateTime::currentDateTime();
    curDate = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    fout << curDate << endl;
    fout << lastWords << endl;
    fout << curChar.size() << endl;
    for (auto it = curChar.begin(); it != curChar.end(); ++ it) {
        fout << it->first << " " << it->second.second << endl;
        map<QString, QString> &args = it->second.first;
        fout << args.size() << endl;
        for (auto it2 = args.begin(); it2 != args.end(); ++ it2) {
            fout << it2->first << " " << it2->second << endl;
        }
    }
    fout << curScene << endl;
    fout << curMask << endl;
    fout << curBGM << endl;
    fout << this->fname << endl;
    fout << lineNum << endl;
    fout << galCharAnimator.charScale.size() << endl;
    for (auto it = galCharAnimator.charScale.begin(); it != galCharAnimator.charScale.end(); ++ it) {
        fout << it->first << " " << it->second << endl;
    }
    f.close();
}

void GALStatus::loadFrom(QString fname) {
    QFile f(fname);
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "GALStatus::loadFrom - Cannot open file";
        return;
    }
    QTextStream fin(&f);
    curDate = fin.readLine();
    lastWords = fin.readLine();
    int mapSize;
    fin >> mapSize;
    curChar.clear();
    for (int i = 0; i < mapSize; ++ i) {
        QString s1;
        int i3;
        fin >> s1 >> i3;
        int argsSize;
        fin >> argsSize;
        map<QString, QString> args;
        for (int j = 0; j < argsSize; ++ j) {
            QString q1, q2;
            fin >> q1 >> q2;
            args[q1] = q2;
        }
        curChar[s1] = make_pair(args, i3);
    }
    fin >> curScene;
    fin >> curMask;
    fin >> curBGM;
    fin >> this->fname;
    fin >> lineNum;
    fin >> mapSize;
    galCharAnimator.charScale.clear();
    for (int i = 0; i < mapSize; ++ i) {
        QString s1;
        double i3;
        fin >> s1 >> i3;
        galCharAnimator.charScale[s1] = i3;
    }
    f.close();
}

void GALStatus::update() {
    galCharAnimator.update();
    galSceneChanger.update();
}
