#ifndef DTH11_H
#define DTH11_H

#include <QWidget>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <QTimer>
#include <QString>

#define HIGH_TIME 32
typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;

namespace Ui {
class DTH11;
}

class DTH11 : public QWidget
{
    Q_OBJECT

public:
    explicit DTH11(QWidget *parent = 0);
    ~DTH11();
    void dht11_init();
    uint8 read_dht11_dat();

private slots:
    void data_display();

private:
    Ui::DTH11 *ui;
    QTimer *qtimer;
    int pinNumber =1;  //use gpio1 to read data
    uint32 databuf;
};

#endif // DTH11_H
