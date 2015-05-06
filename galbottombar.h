#ifndef GALBOTTOMBAR_H
#define GALBOTTOMBAR_H

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QImage>

class GALBottomBar
{
public:
    GALBottomBar();
    ~GALBottomBar();

    void mouseMove(QMouseEvent *e);
    void paint(QPainter &painter);

    int focus;
private:
    int left;
    int width[5], pos_x[5], pos_y[5];
    QString func[5];
    QImage board, img[5], img_hl[5];
};

#endif // GALBOTTOMBAR_H
