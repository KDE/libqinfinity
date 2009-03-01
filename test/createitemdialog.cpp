#include "createitemdialog.h"

#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "createitemdialog.moc"

CreateItemDialog::CreateItemDialog( const QString &text,
    QWidget *parent )
    : QDialog( parent )
{
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel( text );
    itemEdit = new QLineEdit();
    cancelButton = new QPushButton( "cancel" );
    okButton = new QPushButton( "ok" );

    nameLayout->addWidget( nameLabel );
    nameLayout->addWidget( itemEdit );
    buttonLayout->addWidget( cancelButton );
    buttonLayout->addWidget( okButton );
    mainLayout->addLayout( nameLayout );
    mainLayout->addLayout( buttonLayout );
    setLayout( mainLayout );
    
    connect( okButton, SIGNAL(clicked(bool)),
        this, SLOT(ok()) );
    connect( cancelButton, SIGNAL(clicked(bool)),
        this, SLOT(cancel()) );
}

QString CreateItemDialog::itemName() const
{
    return itemEdit->text();
}

void CreateItemDialog::cancel()
{
    done(0);
}

void CreateItemDialog::ok()
{
    done(0);
}

