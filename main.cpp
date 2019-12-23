#include "framedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrameDialog w;
    w.show();

    return a.exec();
}
