/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue Nov 19 16:51:17 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditVille_2;
    QPushButton *pushButtonRechercher;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEditVille_3;
    QPushButton *pushButtonTaille;
    QPushButton *pushButtonTaille_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(891, 345);
        Dialog->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"   background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    /*background-color: red;*/\n"
"}\n"
"QLineEdit\n"
"{\n"
"    color: #b1b1b1;\n"
"   background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4"
                        "a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}"));
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditVille_2 = new QLineEdit(Dialog);
        lineEditVille_2->setObjectName(QString::fromUtf8("lineEditVille_2"));
        lineEditVille_2->setMinimumSize(QSize(178, 0));
        lineEditVille_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(lineEditVille_2);

        pushButtonRechercher = new QPushButton(Dialog);
        pushButtonRechercher->setObjectName(QString::fromUtf8("pushButtonRechercher"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../QtMeteo-build-desktop-Desktop_Qt_4_8_1_for_GCC__Qt_SDK__Release/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRechercher->setIcon(icon);

        horizontalLayout->addWidget(pushButtonRechercher);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEditVille_3 = new QLineEdit(Dialog);
        lineEditVille_3->setObjectName(QString::fromUtf8("lineEditVille_3"));
        lineEditVille_3->setMinimumSize(QSize(178, 0));
        lineEditVille_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(lineEditVille_3);

        pushButtonTaille = new QPushButton(Dialog);
        pushButtonTaille->setObjectName(QString::fromUtf8("pushButtonTaille"));
        pushButtonTaille->setMaximumSize(QSize(31, 16777215));

        horizontalLayout_3->addWidget(pushButtonTaille);

        pushButtonTaille_2 = new QPushButton(Dialog);
        pushButtonTaille_2->setObjectName(QString::fromUtf8("pushButtonTaille_2"));
        pushButtonTaille_2->setMaximumSize(QSize(31, 16777215));

        horizontalLayout_3->addWidget(pushButtonTaille_2);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(448, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        graphicsView_2 = new QGraphicsView(Dialog);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setMinimumSize(QSize(251, 192));

        horizontalLayout_2->addWidget(graphicsView_2);

        graphicsView = new QGraphicsView(Dialog);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(256, 192));
        QFont font;
        font.setFamily(QString::fromUtf8("Meera"));
        graphicsView->setFont(font);
        graphicsView->setStyleSheet(QString::fromUtf8("border-radius : 50px;\n"
"border-color: rgb(85, 85, 85);"));

        horizontalLayout_2->addWidget(graphicsView);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        QWidget::setTabOrder(lineEditVille_2, lineEditVille_3);
        QWidget::setTabOrder(lineEditVille_3, pushButtonRechercher);
        QWidget::setTabOrder(pushButtonRechercher, pushButtonTaille);
        QWidget::setTabOrder(pushButtonTaille, pushButtonTaille_2);
        QWidget::setTabOrder(pushButtonTaille_2, graphicsView_2);
        QWidget::setTabOrder(graphicsView_2, graphicsView);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButtonRechercher->setText(QApplication::translate("Dialog", "Rechercher", 0, QApplication::UnicodeUTF8));
        pushButtonTaille->setText(QApplication::translate("Dialog", "<<", 0, QApplication::UnicodeUTF8));
        pushButtonTaille_2->setText(QApplication::translate("Dialog", ">>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
