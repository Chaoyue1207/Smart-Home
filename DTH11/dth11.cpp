#include "dth11.h"
#include "ui_dth11.h"
#include <wiringPi.h>
#include <iostream>

DTH11::DTH11(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DTH11)
{
    ui->setupUi(this);
    qtimer = new QTimer(this);

    connect(qtimer, SIGNAL(timeout()), this, SLOT(data_display()));
}

DTH11::~DTH11()
{
    delete ui;
}

void DTH11::dht11_init()
{
    printf("Use GPIO1 to read data!\n");

    if (-1 == wiringPiSetup()) {
    printf("Setup wiringPi failed!");
    return;
    }

    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level

    printf("Enter OS-------\n");

    qtimer->start(100);
}

uint8 DTH11::read_dht11_dat()
{
    uint8 crc;
    uint8 i;

    pinMode(pinNumber,OUTPUT); // set mode to output
    digitalWrite(pinNumber, 0); // output a high level
    delay(25);
    digitalWrite(pinNumber, 1); // output a low level
    pinMode(pinNumber, INPUT); // set mode to input
    pullUpDnControl(pinNumber,PUD_UP);

    delayMicroseconds(27);
    if(digitalRead(pinNumber)==0) //SENSOR ANS
    {
        while(!digitalRead(pinNumber)); //wait to high

        for(i=0;i<32;i++)
        {
            while(digitalRead(pinNumber)); //data clock start
            while(!digitalRead(pinNumber)); //data start
            delayMicroseconds(HIGH_TIME);
            databuf*=2;
            if(digitalRead(pinNumber)==1) //1
            {
                databuf++;
            }
        }
        for(i=0;i<8;i++)
        {
            while(digitalRead(pinNumber)); //data clock start
            while(!digitalRead(pinNumber)); //data start
            delayMicroseconds(HIGH_TIME);
            crc*=2;
            if(digitalRead(pinNumber)==1) //1
            {
                crc++;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void DTH11::data_display()
{
    pinMode(pinNumber,OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level
    delay(3000);
    if(read_dht11_dat())
    {
        QString tmp = QString::number((databuf>>8)&0xff, 10);
        QString rh = QString::number((databuf>>24)&0xff, 10);
        ui->lb_tmpdisplay->setText(tmp);
        ui->lb_rhdisplay->setText(rh);
//        printf("Congratulations ! Sensor data read ok!\n");
//        printf("RH:%d.%d\n",(databuf>>24)&0xff,(databuf>>16)&0xff);
//        printf("TMP:%d.%d\n",(databuf>>8)&0xff,databuf&0xff);
        databuf=0;
    }
    else
    {
        ui->lb_tmpdisplay->setText("Sorry! Sensor dosent ans!");
//        printf("Sorry! Sensor dosent ans!\n");
        databuf=0;
    }
}
