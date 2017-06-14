#include "mainWindow.hpp"
#include <iostream>
#include<QScrollArea>
#include<QScrollBar>
#include<Qt>
#include<QFontMetrics>
mainWindow::mainWindow()
{
	setGeometry(10,10,1000,500);
	setWindowTitle("GRI-System");
	createLayout();
	createMessageBox();
	createWriteBox();
	addAvatars();
}

void mainWindow::createWriteBox()
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

void mainWindow::createMessageBox()
{
	messageBox = new QVBoxLayout();
	rightSide->addLayout(messageBox);
	messageText=new QTextEdit(this);
	messageText->setReadOnly(true);
	messageBox->addWidget(messageText);
	messageTextLayout = new QVBoxLayout();
}	

void mainWindow::addAvatars()
{
	leftLabel = new QLabel(this);
	leftLabel->setGeometry(0,0,300,1800);
	
	avLay = new QVBoxLayout();
	avLay->setAlignment(Qt::AlignTop);
	leftLabel->setLayout(avLay);
	
	scrollArea = new QScrollArea(this);
	scrollArea->setGeometry(0,0,320,1150);
	scrollArea->setMaximumWidth(320);
	scrollArea->setWidget(leftLabel);

	scrollArea->setWidgetResizable(false);
	for (int i=0;i<25;++i){
		createAvatar();
	}

	leftSide->addWidget(scrollArea);
}

void mainWindow::createLayout(){
	
	mainLayout = new QGridLayout();
	leftSide   = new QVBoxLayout();
	rightSide  = new QVBoxLayout();
	
	mainLayout->addLayout(leftSide,0,0);
	mainLayout->addLayout(rightSide,0,1);

	setLayout(mainLayout);
	
}

void mainWindow::createAvatar()
{
	Avatar* a = new Avatar();
	avLay->addWidget(a);
	avatars.push_back(a);
}

void mainWindow::sendMessage()
{
	messages.push_back("");
	messages[0]+="\n>>>>>>>>>>\n";
	messages[0]+=(textEdit->toPlainText()+"\n");
	messageText->setText(messages[0]);
	textEdit->setText(" ");
}
