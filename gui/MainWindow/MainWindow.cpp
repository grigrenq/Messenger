#include <iostream>
#include <QScrollArea>
#include <QScrollBar>
#include <Qt>
#include <QFontMetrics>

#include "MainWindow.hpp"

MainWindow::mainWindow()
{
	setGeometry(10,10,1000,500);
	setWindowTitle("GRI-System");
	createLayout();
	addAvatars();
}


void MainWindow::addAvatars()
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
	for (auto a : avatars) {
		avLay->addWidget(a);
	}

	leftSide->addWidget(scrollArea);
}

void MainWindow::addAvatar(Avatar* a)
{
	avLay.addWidget(a);
}

void MainWindow::createLayout(){
	
	mainLayout = new QGridLayout();
	leftSide   = new QVBoxLayout();
	rightSide  = new QVBoxLayout();
	
	mainLayout->addLayout(leftSide,0,0);
	mainLayout->addLayout(rightSide,0,1);

	setLayout(mainLayout);
	
}

void MainWindow::createAvatar()
{
	Avatar* a = new Avatar();
	avLay->addWidget(a);
	avatars.push_back(a);
}

void MainWindow::sendMessage()
{
	messages.push_back("");
	messages[0]+="\n>>>>>>>>>>\n";
	messages[0]+=(textEdit->toPlainText()+"\n");
	messageText->setText(messages[0]);
	textEdit->setText(" ");
}
