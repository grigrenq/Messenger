#include "WriteBox.hpp"



WriteBox::WriteBox()
{
	//writeBox = new QHBoxLayout();
	//textEdit = new QTextEdit();
	//textEdit->set
}

void WriteBox::createWriteBox()
{
	
	writeBox=new QHBoxLayout();
	rightSide->addLayout(writeBox);
	textEdit = new QTextEdit();
	textEdit->setMinimumSize(500,70);
	textEdit->setMaximumSize(800,70);
	sendButton = new QPushButton("Send");
	sendButton->setStyleSheet("QPushButton{background-color: #456ba8; color: white;}");
	sendButton->setMaximumSize(150,30);
	writeBox->addWidget(textEdit);
	writeBox->addWidget(sendButton);
	rightSide->addLayout(writeBox);
	QObject::connect(sendButton,SIGNAL(clicked()),this,SLOT(sendMessage()));

}
