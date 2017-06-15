#include <iostream>
#include <QScrollArea>
#include <QScrollBar>
#include <Qt>
#include <QFontMetrics>

#include "Avatar.hpp"
#include "MainWindow.hpp"

MainWindow::MainWindow(Controller& c)
	: messageBox(*this)
	, writeBox(*this)
	, controller(c)
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
	avLay->addWidget(a);
}

void MainWindow::createLayout(){
	
	mainLayout = new QGridLayout();
	leftSide   = new QVBoxLayout();
	rightSide  = new QVBoxLayout();
	
	mainLayout->addLayout(leftSide,0,0);
	mainLayout->addLayout(rightSide,0,1);

	setLayout(mainLayout);
}

/*
void MainWindow::createAvatar()
{
	Avatar* a = new Avatar();
	avLay->addWidget(a);
	avatars.push_back(a);
}*/


void MainWindow::updateMessageBox()
{
   	messageBox.update(userPtr->getLogin(), userPtr->getMessages()); 
}

void MainWindow::sendMessage(String& msg)
{
	if(userPtr == nullptr) {
		return;
	}
	String toUser = userPtr->getLogin();
	userPtr->addMessage(controller.getLogin() + delim + msg);
	controller.sendMessageToUser(toUser, msg);
	messageBox.update(userPtr->getLogin(), userPtr->getMessages());
}

void MainWindow:: updateMainWindow(User& u)
{
	auto it = find(u);
	if (it == avatars.end()) {
		avatars.push_back(new Avatar(u, *this));
		addAvatar(avatars.back());
	} else {
		(*it)->setStatus(u.getStatus());
		if (userPtr->getLogin() == u.getLogin()) {
			messageBox.update(u.getLogin(), u.getMessages());
		} else {
			(*it)->incrementCount();
		}
	}
}
void MainWindow::setUser(User& u)
{
   	userPtr = &u; 
}

void MainWindow::createAvatars(Users& users) 
{
	for (auto it = users.begin(); it != users.end(); ++it) {
		avatars.push_back(new Avatar(*it, *this));
	}
	addAvatars();
	//show();
}
MainWindow::AvatarsIter MainWindow::find(const User& u)
{
	AvatarsIter it;
	for (; it != avatars.end(); ++it) {
		if ((*it)->getLogin() == u.getLogin()) {
			return it;
		}
	}
	return it;
}







