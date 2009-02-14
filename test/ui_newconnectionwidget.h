/********************************************************************************
** Form generated from reading ui file 'newconnectionwidget.ui'
**
** Created: Sat Feb 14 05:35:29 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEWCONNECTIONWIDGET_H
#define UI_NEWCONNECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newConnectionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *hostnameLabel;
    QLineEdit *hostnameLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelPushButton;
    QPushButton *okPushButton;

    void setupUi(QWidget *newConnectionWidget)
    {
    if (newConnectionWidget->objectName().isEmpty())
        newConnectionWidget->setObjectName(QString::fromUtf8("newConnectionWidget"));
    newConnectionWidget->resize(259, 110);
    verticalLayout = new QVBoxLayout(newConnectionWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hostnameLabel = new QLabel(newConnectionWidget);
    hostnameLabel->setObjectName(QString::fromUtf8("hostnameLabel"));

    gridLayout->addWidget(hostnameLabel, 0, 0, 1, 1);

    hostnameLineEdit = new QLineEdit(newConnectionWidget);
    hostnameLineEdit->setObjectName(QString::fromUtf8("hostnameLineEdit"));

    gridLayout->addWidget(hostnameLineEdit, 0, 1, 1, 1);

    portLabel = new QLabel(newConnectionWidget);
    portLabel->setObjectName(QString::fromUtf8("portLabel"));

    gridLayout->addWidget(portLabel, 1, 0, 1, 1);

    portLineEdit = new QLineEdit(newConnectionWidget);
    portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));

    gridLayout->addWidget(portLineEdit, 1, 1, 1, 1);


    verticalLayout->addLayout(gridLayout);

    verticalSpacer = new QSpacerItem(20, 77, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    cancelPushButton = new QPushButton(newConnectionWidget);
    cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));

    horizontalLayout->addWidget(cancelPushButton);

    okPushButton = new QPushButton(newConnectionWidget);
    okPushButton->setObjectName(QString::fromUtf8("okPushButton"));

    horizontalLayout->addWidget(okPushButton);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi(newConnectionWidget);

    QMetaObject::connectSlotsByName(newConnectionWidget);
    } // setupUi

    void retranslateUi(QWidget *newConnectionWidget)
    {
    newConnectionWidget->setWindowTitle(QApplication::translate("newConnectionWidget", "Form", 0, QApplication::UnicodeUTF8));
    hostnameLabel->setText(QApplication::translate("newConnectionWidget", "Hostname:", 0, QApplication::UnicodeUTF8));
    portLabel->setText(QApplication::translate("newConnectionWidget", "Port:", 0, QApplication::UnicodeUTF8));
    cancelPushButton->setText(QApplication::translate("newConnectionWidget", "Cancel", 0, QApplication::UnicodeUTF8));
    okPushButton->setText(QApplication::translate("newConnectionWidget", "Ok", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(newConnectionWidget);
    } // retranslateUi

};

namespace Ui {
    class newConnectionWidget: public Ui_newConnectionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCONNECTIONWIDGET_H
