#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include "galscene.h"
namespace Ui {
class Widget;
}

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:
    Ui::Widget *ui;
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
