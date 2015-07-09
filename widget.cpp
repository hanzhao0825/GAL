#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
Widget::Widget() :
    QWidget()
{
    setFixedSize(1080, 720);
    setAutoFillBackground(false);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(20);
    elapsed = 0;
    setMouseTracking(true);


    QResource::registerResource(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/rcc/char.rcc"));
    QResource::registerResource(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/rcc/scene.rcc"));
    QResource::registerResource(QDir::toNativeSeparators(QApplication::applicationDirPath()+"/rcc/bgm.rcc"));

    galScene.jumpToScript("DEMO");


}

Widget::~Widget()
{

}

void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    galScene.update();
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter.drawRect(0, 0, 1080, 720);
    galScene.paint(painter);
    painter.end();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    galScene.mousePress(e);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    galScene.mouseMove(e);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    galScene.keyPress(e);
}
