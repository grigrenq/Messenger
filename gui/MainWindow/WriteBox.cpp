#include "WriteBox.hpp"



WriteBox::WriteBox(MainWindow &mw)
{
	createWriteBox();
	mw.rightSide->addLayout(writebox);
}

void WriteBox::createWriteBox()
{
	
	writeBox=new QHBoxLayout();
	textEdit = new QTextEdit();
	textEdit->setMinimumSize(500,70);
	textEdit->setMaximumSize(800,70);
	sendButton = new QPushButton("Send");
	sendButton->setStyleSheet("QPushButton{background-color: #456ba8; color: white;}");
	sendButton->setMaximumSize(150,30);
	writeBox->addWidget(textEdit);
	writeBox->addWidget(sendButton);
	QObject::connect(sendButton,SIGNAL(clicked()),this,SLOT(sendMessage()));

}

void WriteBox::sendMessage()
{
	mw.sendMessage(textEdit.text());
}
