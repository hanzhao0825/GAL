#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
Widget::Widget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setAutoFillBackground(false);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(15);
    elapsed = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    qDebug() << elapsed;
    update();
}
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    galScene.paint(painter);
    painter.end();
}
