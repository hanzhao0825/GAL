#include "galstatus.h"

GALStatus::GALStatus()
{
    fname = "";
    curDate = "";
}

GALStatus::~GALStatus()
{

}


void GALStatus::saveTo(QString fname) {
//    qDebug() << "Saving To " << fname;
    QFile f(fname);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream fout(&f);
    fout << curChar.size() << endl;
    for (auto it = curChar.begin(); it != curChar.end(); ++ it) {
        fout << it->first << " " << it->second.first << " " << it->second.second;
    }
    fout << curScene << endl;
    fout << curBGM << endl;
    fout << this->fname << endl;
    fout << lineNum << endl;
    QDateTime current_date_time = QDateTime::currentDateTime();
    curDate = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    fout << curDate << endl;
    fout << lastWords << endl;
    f.close();
}

void GALStatus::loadFrom(QString fname) {
//    qDebug() << "Loading from " << fname;
    QFile f(fname);
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file";
        return;
    }
    QTextStream fin(&f);
    QString lineStr;
    int mapSize;
    fin >> mapSize;
    curChar.clear();
    for (int i = 0; i < mapSize; ++ i) {
        QString s1, s2;
        int i3;
        fin >> s1 >> s2 >> i3;
        curChar[s1] = make_pair(s2, i3);
    }
    fin >> curScene;
    fin >> curBGM;
    fin >> this->fname;
    fin >> lineNum;
    curDate = fin.readLine();
    curDate = fin.readLine();
    fin >> lastWords;
    f.close();
}

void GALStatus::clear(){
    int lineNum;
    curBGM = "";
    curChar.clear();
    curDate = "";
    curScene = "";
    fname = "";
    lineNum = 0;
}
