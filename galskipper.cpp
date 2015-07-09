#include "galskipper.h"

GALSkipper::GALSkipper()
{
    skip = false;
    QFile f(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/data/skipper"));
    if (! f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "GALSkipper::GALSkipper - Cannot open file";
        return;
    }
    QTextStream fin(&f);
    QString fname;
    int lineSum, t;
    fin >> lineSum;
    for (int i = 0; i < lineSum; i++) {
        fin >> fname >> t;
        lines[fname] = t;
    }
    f.close();
}

GALSkipper::~GALSkipper()
{

}

void GALSkipper::save() {
    QFile f(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/data/skipper"));
    if (! f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "GALSkipper::save - Cannot open file";
        return;
    }
    QTextStream fout(&f);
    fout << lines.size() << endl;
    for (auto it = lines.begin(); it != lines.end(); ++it) {
        fout << it->first << " " << it->second << endl;
    }
    f.close();
}
