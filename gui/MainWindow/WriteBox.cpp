#include <QLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QPixmap>
#include <Qt>
#include <QString>
#include <string>
#include "MainWindow.hpp"
#include "WriteBox.hpp"

#include <cmath>


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

bool WriteBox::isEmptyWriteBox()
{
    return textEdit_->toPlainText().isEmpty();
}

void WriteBox::sendMessage()
{
	String msg = textEdit_->toPlainText().toStdString();
	if (msg.size() < maxMessageSize) {
		mainWindow_.sendMessage(msg);
	} else {
		int c = ceil(msg.size() / static_cast<float>(maxMessageSize));
		size_t begin = 0;
		for (int i = 0; i < c; ++i) {
			String s(msg.substr(begin, maxMessageSize));
			mainWindow_.sendMessage(s);
			begin += maxMessageSize;
		}
	}
        textEdit_->setText("");
}

QLayout* WriteBox::getWriteBox()
{
	return writeBox_;
}
