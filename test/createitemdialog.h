#ifndef QINF_TEST_CREATEITEMDIALOG_H
#define QINF_TEST_CREATEITEMDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class CreateItemDialog
    : public QDialog
{

    public:
        CreateItemDialog( const QString &text,
            QWidget *parent = 0 );

    private:
        QLineEdit *itemName;
        QPushButton *okButton;
        QPushButton *cancelButton;

};

#endif

