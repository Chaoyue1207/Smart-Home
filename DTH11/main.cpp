#include "dth11.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DTH11 w;
    w.dht11_init();
    w.show();

    return a.exec();
}
