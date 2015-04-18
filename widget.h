#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include "galscene.h"
namespace Ui {
class Widget;
}

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    GALScene galScene;
    int elapsed;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // WIDGET_H
