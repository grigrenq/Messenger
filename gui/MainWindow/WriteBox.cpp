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
	: mainWindow(mw)
{
	createWriteBox();
//`	mainWindow.rightSide->addLayout(writebox);
}

void WriteBox::createWriteBox()
{
	writeBox = new QHBoxLayout();
	textEdit = new QTextEdit();
	textEdit->setMinimumSize(500,70);
	textEdit->setMaximumHeight(70);
	sendButton = new QPushButton();
	sendButton->setMaximumSize(100,100);
	QPixmap sendPic("../resources/send.png");
	sendButton->setIcon(sendPic);
	QRegion* region = new QRegion(*(new QRect(sendButton->x()+10,sendButton->y()+10,50,50)),QRegion::Ellipse);
	sendButton->setMask(*region);
	QSize buttonSize(50,50);
	sendButton->setIconSize(buttonSize);
	writeBox->addWidget(textEdit);
	writeBox->addWidget(sendButton);
	writeBox->setAlignment(Qt::AlignLeft);
	QObject::connect(sendButton,SIGNAL(clicked()),this,SLOT(sendMessage()));

}

void WriteBox::sendMessage()
{
	std::string a=textEdit->toPlainText().toStdString();
	mainWindow.sendMessage(a);
}

QLayout* WriteBox::getWriteBox()
{
	return writeBox;
}
