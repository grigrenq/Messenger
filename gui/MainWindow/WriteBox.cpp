#include <QLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QPixmap>
#include <Qt>
#include <QString>
#include <string>
#include "MainWindow.hpp"
#include "WriteBox.hpp"


WriteBox::WriteBox(MainWindow& mw)
	: mainWindow_(mw)
{
	createWriteBox();
//`	mainWindow.rightSide->addLayout(writebox);
}

void WriteBox::createWriteBox()
{
	writeBox_ = new QHBoxLayout();
	textEdit_ = new QTextEdit();
	textEdit_->setMinimumSize(500,70);
	textEdit_->setMaximumHeight(70);
	sendButton_ = new QPushButton();
	sendButton_->setMaximumSize(100,100);
	QPixmap sendPic("../resources/send.png");
	sendButton_->setIcon(sendPic);
	QRegion* region = new QRegion(*(new QRect(sendButton_->x()+10,sendButton_->y()+10,50,50)),QRegion::Ellipse);
	sendButton_->setMask(*region);
	QSize buttonSize(50,50);
	sendButton_->setIconSize(buttonSize);
	writeBox_->addWidget(textEdit_);
	writeBox_->addWidget(sendButton_);
	writeBox_->setAlignment(Qt::AlignLeft);
	QObject::connect(sendButton_,SIGNAL(clicked()),this,SLOT(sendMessage()));

}

void WriteBox::sendMessage()
{
	String a=textEdit_->toPlainText().toStdString();
	mainWindow_.sendMessage(a);
}

QLayout* WriteBox::getWriteBox()
{
	return writeBox_;
}
