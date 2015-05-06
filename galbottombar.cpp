#include "galbottombar.h"

GALBottomBar::GALBottomBar()
{
    focus = -1;
    left = 787;
    width[0] = 40;
    width[1] = 40;
    width[2] = 40;
    width[3] = 40;
    width[4] = 50;

    pos_x[0] = 790;
    pos_x[1] = 830;
    pos_x[2] = 870;
    pos_x[3] = 910;
    pos_x[4] = 955;

    pos_y[0] = 695;
    pos_y[1] = 698;
    pos_y[2] = 698;
    pos_y[3] = 698;
    pos_y[4] = 700;

    func[0] = "load";
    func[1] = "save";
    func[2] = "skip";
    func[3] = "log";
    func[4] = "system";

    board = QImage("./res/gal/image/icon/bottombar.png");
    for (int i = 0; i < 5; i ++) {
        img[i] = QImage(QString("./res/gal/image/icon/bottombar_img_")+func[i]+".png");
        img_hl[i] = QImage(QString("./res/gal/image/icon/bottombar_img_")+func[i]+"_hl.png");
    }
}

GALBottomBar::~GALBottomBar()
{

}

void GALBottomBar::paint(QPainter &painter) {
     painter.drawImage(0,665,board);
     for (int i = 0; i < 5; i ++) {
         if (focus == i) {
             painter.drawImage(pos_x[i], pos_y[i], img_hl[i]);
         } else {
             painter.drawImage(pos_x[i], pos_y[i], img[i]);
         }
     }
}

void GALBottomBar::mouseMove(QMouseEvent *e) {
    focus = -1;
    if (e->y() < 700 || e->x() < left) return;
    int t = left;
    for (int i = 0; i < 5; i ++) {
        if (e->x() < t + width[i]) {
            focus = i;
            break;
        }
        t += width[i];
    }
}
