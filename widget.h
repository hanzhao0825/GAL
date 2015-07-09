#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include "galscene.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:

    GALScene galScene;
    int elapsed;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // WIDGET_H
