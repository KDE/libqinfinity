#ifndef QINF_TEST_CREATEITEMDIALOG_H
#define QINF_TEST_CREATEITEMDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class CreateItemDialog
    : public QDialog
{
    Q_OBJECT

    public:
        CreateItemDialog( const QString &text,
            QWidget *parent = 0 );

        QString itemName() const;

    private Q_SLOTS:
        void cancel();
        void ok();

    private:
        QLineEdit *itemEdit;
        QPushButton *okButton;
        QPushButton *cancelButton;

};

#endif

