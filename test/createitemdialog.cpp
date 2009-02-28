#include "createitemdialog.h"

#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

CreateItemDialog::CreateItemDialog( const QString &text,
    QWidget *parent )
    : QDialog( parent )
{
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel( text );
    itemName = new QLineEdit();
    okButton = new QPushButton( "ok" );
    cancelButton = new QPushButton( "cancel" );
    nameLayout->addWidget( nameLabel );
    nameLayout->addWidget( itemName );
    buttonLayout->addWidget( okButton );
    buttonLayout->addWidget( cancelButton );
    mainLayout->addLayout( nameLayout );
    mainLayout->addLayout( buttonLayout );
    setLayout( mainLayout );
}

