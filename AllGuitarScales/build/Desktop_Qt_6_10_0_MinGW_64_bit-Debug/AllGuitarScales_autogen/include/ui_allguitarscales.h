/********************************************************************************
** Form generated from reading UI file 'allguitarscales.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLGUITARSCALES_H
#define UI_ALLGUITARSCALES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AllGuitarScales
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AllGuitarScales)
    {
        if (AllGuitarScales->objectName().isEmpty())
            AllGuitarScales->setObjectName("AllGuitarScales");
        AllGuitarScales->resize(800, 600);
        centralwidget = new QWidget(AllGuitarScales);
        centralwidget->setObjectName("centralwidget");
        AllGuitarScales->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AllGuitarScales);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        AllGuitarScales->setMenuBar(menubar);
        statusbar = new QStatusBar(AllGuitarScales);
        statusbar->setObjectName("statusbar");
        AllGuitarScales->setStatusBar(statusbar);

        retranslateUi(AllGuitarScales);

        QMetaObject::connectSlotsByName(AllGuitarScales);
    } // setupUi

    void retranslateUi(QMainWindow *AllGuitarScales)
    {
        AllGuitarScales->setWindowTitle(QCoreApplication::translate("AllGuitarScales", "AllGuitarScales", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AllGuitarScales: public Ui_AllGuitarScales {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLGUITARSCALES_H
