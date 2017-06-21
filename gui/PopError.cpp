#include <QPushButton>
#include <QString>
#include "PopError.hpp"

PopError::PopError()
{
    createMessageBox();
    handleConnection();
}

void PopError::setTextSlot(const QString& s)
{
    messageBox->setText(s);
}

void PopError::executeSlot()
{
    messageBox->exec();
}

void PopError::setText(const String& s)
{
    QString qstr = QString::fromStdString(s);
    emit setTextSignal(qstr);
}

void PopError::execute()
{
    emit executeSignal();
}

void PopError::handleConnection()
{
    connect(this,SIGNAL(executeSignal()), this, SLOT(executeSlot()));
    connect(this,SIGNAL(setTextSignal(const QString&)), this, SLOT(setTextSlot(const QString&)));
}

void PopError::createMessageBox()
{
    messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("Error!");
    messageBox->setDefaultButton(QMessageBox::Ok);
}
