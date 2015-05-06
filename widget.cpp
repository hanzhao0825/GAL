#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1080, 720);
    setAutoFillBackground(false);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(16);
    elapsed = 0;
    setMouseTracking(true);
    galScene.jumpToScript("0.0.0");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
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
