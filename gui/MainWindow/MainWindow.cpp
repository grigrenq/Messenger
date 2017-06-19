#include <iostream>
#include <QScrollArea>
#include <QScrollBar>
#include <Qt>
#include <QFontMetrics>

#include "MainWindow.hpp"
#include "Avatar.hpp"

const char delim = '%';

MainWindow::MainWindow(Controller& c)
	: messageBox(new MessageBox(*this))
	, writeBox(new WriteBox(*this))
	, controller(c)
{
	setGeometry(10,10,1000,500);
	setWindowTitle("GRI-System");
	createLayout();
	addAvatars();

	QObject::connect(this, SIGNAL(showSignal()), this, SLOT(showSlot()));
}

void MainWindow::addAvatars()
{
	avLay = new QVBoxLayout();
	avLay->setAlignment(Qt::AlignTop);

	scrollArea = new QScrollArea(this);
	scrollArea->move(0,0);
	scrollArea->setMaximumWidth(250);
	scrollArea->setMinimumWidth(250);

	for (auto a : avatars) {
		avLay->addWidget(a);
	}
	QWidget* scrollWidget = new QWidget;
	scrollWidget->setLayout(avLay);
	scrollArea->setWidget(scrollWidget);
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
	

	rightSide->addLayout(messageBox->getMessageBox());
	rightSide->addLayout(writeBox->getWriteBox());
	
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
   	messageBox->update(userPtr->getLogin(), userPtr->getMessages()); 
}

void MainWindow::sendMessage( String& msg)
{
	if(userPtr == nullptr) {
		return;
	}
	messageBox->getMessageText()->verticalScrollBar()->setValue(messageBox->getMessageText()->verticalScrollBar()->maximum());
	String toUser = userPtr->getLogin();
	userPtr->addMessage(controller.getLogin() + delim + msg);
	controller.sendMessageToUser(toUser, msg);
	messageBox->update(userPtr->getLogin(), userPtr->getMessages());
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
			messageBox->update(u.getLogin(), u.getMessages());
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







void MainWindow::showWindow()
{
	emit showSignal();
}

void MainWindow::showSlot()
{
	this->show();
}
