/********************************************************************************
** Form generated from reading UI file 'dth11.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTH11_H
#define UI_DTH11_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DTH11
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *lb_tmpdisplay;
    QLabel *label_2;
    QLabel *lb_rhdisplay;

    void setupUi(QWidget *DTH11)
    {
        if (DTH11->objectName().isEmpty())
            DTH11->setObjectName(QStringLiteral("DTH11"));
        DTH11->resize(400, 300);
        formLayoutWidget = new QWidget(DTH11);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(110, 90, 160, 80));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lb_tmpdisplay = new QLabel(formLayoutWidget);
        lb_tmpdisplay->setObjectName(QStringLiteral("lb_tmpdisplay"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lb_tmpdisplay);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lb_rhdisplay = new QLabel(formLayoutWidget);
        lb_rhdisplay->setObjectName(QStringLiteral("lb_rhdisplay"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lb_rhdisplay);


        retranslateUi(DTH11);

        QMetaObject::connectSlotsByName(DTH11);
    } // setupUi

    void retranslateUi(QWidget *DTH11)
    {
        DTH11->setWindowTitle(QApplication::translate("DTH11", "DTH11", 0));
        label->setText(QApplication::translate("DTH11", "TMP", 0));
        lb_tmpdisplay->setText(QApplication::translate("DTH11", "^^^", 0));
        label_2->setText(QApplication::translate("DTH11", "RH", 0));
        lb_rhdisplay->setText(QApplication::translate("DTH11", "^^^", 0));
    } // retranslateUi

};

namespace Ui {
    class DTH11: public Ui_DTH11 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTH11_H
