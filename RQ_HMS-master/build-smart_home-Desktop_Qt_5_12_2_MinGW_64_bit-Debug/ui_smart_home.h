/********************************************************************************
** Form generated from reading UI file 'smart_home.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMART_HOME_H
#define UI_SMART_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_smart_home
{
public:
    QLabel *IP_L;
    QLineEdit *IP;
    QLabel *Port_L;
    QLineEdit *Port;
    QPushButton *connect;
    QPushButton *disconnect;
    QTextBrowser *record;
    QLabel *Video;
    QLabel *Temp_L;
    QLabel *TEM_Unit_L;
    QLabel *HUM_L;
    QLabel *HUM_Unit_L;
    QLabel *AC_L;
    QLabel *Light;
    QLCDNumber *TEM_M;
    QLCDNumber *HUM_M;
    QRadioButton *AtHome;
    QRadioButton *LeaveHome;
    QPushButton *Checked;
    QLabel *fired;

    void setupUi(QWidget *smart_home)
    {
        if (smart_home->objectName().isEmpty())
            smart_home->setObjectName(QString::fromUtf8("smart_home"));
        smart_home->resize(801, 474);
        IP_L = new QLabel(smart_home);
        IP_L->setObjectName(QString::fromUtf8("IP_L"));
        IP_L->setGeometry(QRect(20, 30, 51, 31));
        IP = new QLineEdit(smart_home);
        IP->setObjectName(QString::fromUtf8("IP"));
        IP->setGeometry(QRect(100, 30, 261, 41));
        QFont font;
        font.setPointSize(18);
        IP->setFont(font);
        Port_L = new QLabel(smart_home);
        Port_L->setObjectName(QString::fromUtf8("Port_L"));
        Port_L->setGeometry(QRect(20, 80, 71, 41));
        Port = new QLineEdit(smart_home);
        Port->setObjectName(QString::fromUtf8("Port"));
        Port->setGeometry(QRect(100, 80, 101, 41));
        Port->setFont(font);
        connect = new QPushButton(smart_home);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setGeometry(QRect(550, 10, 101, 51));
        disconnect = new QPushButton(smart_home);
        disconnect->setObjectName(QString::fromUtf8("disconnect"));
        disconnect->setGeometry(QRect(680, 10, 101, 51));
        record = new QTextBrowser(smart_home);
        record->setObjectName(QString::fromUtf8("record"));
        record->setGeometry(QRect(390, 280, 361, 181));
        Video = new QLabel(smart_home);
        Video->setObjectName(QString::fromUtf8("Video"));
        Video->setGeometry(QRect(40, 160, 320, 240));
        Video->setPixmap(QPixmap(QString::fromUtf8(":/jpg/camera.jpg")));
        Video->setAlignment(Qt::AlignCenter);
        Temp_L = new QLabel(smart_home);
        Temp_L->setObjectName(QString::fromUtf8("Temp_L"));
        Temp_L->setGeometry(QRect(370, 110, 181, 41));
        Temp_L->setFont(font);
        TEM_Unit_L = new QLabel(smart_home);
        TEM_Unit_L->setObjectName(QString::fromUtf8("TEM_Unit_L"));
        TEM_Unit_L->setGeometry(QRect(610, 120, 54, 21));
        HUM_L = new QLabel(smart_home);
        HUM_L->setObjectName(QString::fromUtf8("HUM_L"));
        HUM_L->setGeometry(QRect(370, 160, 181, 41));
        HUM_L->setFont(font);
        HUM_Unit_L = new QLabel(smart_home);
        HUM_Unit_L->setObjectName(QString::fromUtf8("HUM_Unit_L"));
        HUM_Unit_L->setGeometry(QRect(613, 170, 61, 21));
        AC_L = new QLabel(smart_home);
        AC_L->setObjectName(QString::fromUtf8("AC_L"));
        AC_L->setGeometry(QRect(370, 210, 161, 31));
        AC_L->setFont(font);
        Light = new QLabel(smart_home);
        Light->setObjectName(QString::fromUtf8("Light"));
        Light->setGeometry(QRect(550, 210, 45, 45));
        Light->setScaledContents(true);
        Light->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        TEM_M = new QLCDNumber(smart_home);
        TEM_M->setObjectName(QString::fromUtf8("TEM_M"));
        TEM_M->setGeometry(QRect(540, 120, 64, 23));
        HUM_M = new QLCDNumber(smart_home);
        HUM_M->setObjectName(QString::fromUtf8("HUM_M"));
        HUM_M->setGeometry(QRect(540, 170, 64, 23));
        AtHome = new QRadioButton(smart_home);
        AtHome->setObjectName(QString::fromUtf8("AtHome"));
        AtHome->setGeometry(QRect(710, 120, 91, 20));
        LeaveHome = new QRadioButton(smart_home);
        LeaveHome->setObjectName(QString::fromUtf8("LeaveHome"));
        LeaveHome->setGeometry(QRect(710, 150, 91, 20));
        Checked = new QPushButton(smart_home);
        Checked->setObjectName(QString::fromUtf8("Checked"));
        Checked->setGeometry(QRect(540, 210, 81, 41));
        fired = new QLabel(smart_home);
        fired->setObjectName(QString::fromUtf8("fired"));
        fired->setEnabled(true);
        fired->setGeometry(QRect(650, 120, 54, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Aharoni"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        fired->setFont(font1);

        retranslateUi(smart_home);

        QMetaObject::connectSlotsByName(smart_home);
    } // setupUi

    void retranslateUi(QWidget *smart_home)
    {
        smart_home->setWindowTitle(QApplication::translate("smart_home", "smart_home", nullptr));
        IP_L->setText(QApplication::translate("smart_home", "<html><head/><body><p><span style=\" font-size:18pt;\">IP\357\274\232</span></p></body></html>", nullptr));
        IP->setText(QString());
        Port_L->setText(QApplication::translate("smart_home", "<html><head/><body><p><span style=\" font-size:18pt;\">Port\357\274\232</span></p></body></html>", nullptr));
        Port->setText(QString());
        connect->setText(QApplication::translate("smart_home", "Connect", nullptr));
        disconnect->setText(QApplication::translate("smart_home", "Cancel", nullptr));
        Video->setText(QString());
        Temp_L->setText(QApplication::translate("smart_home", "Temperature", nullptr));
        TEM_Unit_L->setText(QApplication::translate("smart_home", "\302\260C", nullptr));
        HUM_L->setText(QApplication::translate("smart_home", "Humidity", nullptr));
        HUM_Unit_L->setText(QApplication::translate("smart_home", "%RH", nullptr));
        AC_L->setText(QApplication::translate("smart_home", "Guard", nullptr));
        Light->setText(QString());
        AtHome->setText(QApplication::translate("smart_home", "At home", nullptr));
        LeaveHome->setText(QApplication::translate("smart_home", "Out home", nullptr));
        Checked->setText(QApplication::translate("smart_home", "Checked", nullptr));
        fired->setText(QApplication::translate("smart_home", "*fired*", nullptr));
    } // retranslateUi

};

namespace Ui {
    class smart_home: public Ui_smart_home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMART_HOME_H
