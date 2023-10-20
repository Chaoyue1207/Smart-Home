#include "camera.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera w;
    w.camera_open();
    w.show();

    return a.exec();
}
