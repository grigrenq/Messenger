#include <iostream>
#include <QScrollArea>
#include <QScrollBar>
#include <Qt>
#include <QFontMetrics>
#include <QMetaType>
#include <QIcon>

#include "MainWindow.hpp"
#include "Avatar.hpp"

const char delim = '%';
#include <iostream>

MainWindow::MainWindow(Controller& c)
	: controller_(c)
	, userPtr_(nullptr)
	, messageBox_(new MessageBox(*this))
	, writeBox_(new WriteBox(*this))
	, mainLayout_(nullptr)
	, leftSide_(nullptr)
	, rightSide_(nullptr)
	, avLay_(nullptr)
	, leftLabel_(nullptr)
	, messageLabel_(nullptr)
	, scrollArea_(nullptr)
	, scrollWidget_(nullptr)
	, messageText_(nullptr)
	, messageTextLayout_(nullptr)
	, windowIcon_(nullptr)
{
	qRegisterMetaType<User>("User");
	qRegisterMetaType<Users>("Users");
	setGeometry(10,10,1000,500);
	setWindowIcon();
	setWindowTitle("GRI-System");
	createLayout();

	QObject::connect(this, SIGNAL(showSignal()), this, SLOT(showSlot()));
	QObject::connect(this, SIGNAL(updateSignal(User)), this, SLOT(updateSlot(User)));
	QObject::connect(this, SIGNAL(updateSignal(Users)), this, SLOT(updateSlot(Users)));
}

void MainWindow::addAvatars()
{
	std::cout << __FUNCTION__ << std::endl;
	avLay_->setAlignment(Qt::AlignTop);

	if (scrollArea_ == nullptr) {
		scrollArea_ = new QScrollArea(this);
		scrollArea_->move(0,0);
		scrollArea_->setMaximumWidth(250);
		scrollArea_->setMinimumWidth(250);
	} 

	for (auto a : avatars_) {
		avLay_->addWidget(&(*a));
	}

	if (scrollWidget_ == nullptr) {
		scrollWidget_ = new QWidget;
		scrollWidget_->setLayout(avLay_);
		scrollArea_->setWidget(scrollWidget_);
		leftSide_->addWidget(scrollArea_);
	}
}

void MainWindow::addAvatar(Avatar* a)
{
	avLay_->addWidget(a);
}

void MainWindow::createLayout(){
	
	mainLayout_ = new QGridLayout();
	leftSide_ = new QVBoxLayout();
	rightSide_ = new QVBoxLayout();
	
	avLay_ = new QVBoxLayout();

	rightSide_->addLayout(messageBox_->getMessageBox());
	rightSide_->addLayout(writeBox_->getWriteBox());
	
	mainLayout_->addLayout(leftSide_,0,0);
	mainLayout_->addLayout(rightSide_,0,1);

	setLayout(mainLayout_);
}


void MainWindow::updateMessageBox()
{
	if (messageBox_ == nullptr || userPtr_ == nullptr) {
		throw std::logic_error("asdasdasd");
	}
   	messageBox_->update(userPtr_->getLogin(), userPtr_->getMessages()); 
}

void MainWindow::sendMessage(String& msg)
{
	if (messageBox_ == nullptr || userPtr_ == nullptr) {
		throw std::logic_error("asdasdasd");
	}
	if(userPtr_ == nullptr) {
		return;
	}
	messageBox_->getMessageText()->verticalScrollBar()->setValue(messageBox_->getMessageText()->verticalScrollBar()->maximum());
	String toUser = (userPtr_->getLogin());
	userPtr_->addMessage(controller_.getLogin() + delim + msg);
	controller_.sendMessageToUser(toUser, msg);
	messageBox_->update(userPtr_->getLogin(), userPtr_->getMessages());
}

void MainWindow::updateMainWindow(User& u)
{
	std::cout << "emitting signal updateSignal()\n";
	emit updateSignal(u);
}

void MainWindow::updateMainWindow(Users& users)
{
	emit updateSignal(users);
}

void MainWindow::updateSlot(User u)
{
	std::cout << "slot updateSlot()\n";
	updateMainWindowHelper(u);
}

void MainWindow::updateSlot(Users users)
{
	updateMainWindowHelper(users);
}

void MainWindow::updateMainWindowHelper(User& u)
{
	AvatarsIter it = find(u);
	if (it == avatars_.end()) {
		avatars_.push_back(AvatarPtr(new Avatar(u, *this)));
		addAvatar(&(*avatars_.back()));
	} else {
		std::cout << "....else case:" << (*it)->getLogin() << "|...." << u.getLogin() << "|...." << std::endl;
		//it->reset(new Avatar(u, *this));
		(*it)->setStatus(u.getStatus());
		std::cout << "after it->reset" << std::endl;

		if (userPtr_ == nullptr) {
			return;
		}
		if (userPtr_->getLogin() == u.getLogin()) {
			messageBox_->update((u.getLogin()), u.getMessages());
		} 
	}
}

void MainWindow::updateMainWindowHelper(Users& users)
{
	std::cout << __FUNCTION__ << std::endl;
	avatars_.clear();
	if (avLay_ != nullptr) {
		delete avLay_;
		avLay_ = nullptr;
	}
	if (scrollArea_ != nullptr) {
		//delete scrollArea_;
		//scrollArea_ = nullptr;
	}
	if (scrollWidget_ != nullptr) {
		delete scrollWidget_;
		scrollWidget_ = nullptr;
	}
	std::cout << __FUNCTION__ << std::endl;
	avLay_ = new QVBoxLayout();
	for (auto it = users.begin(); it != users.end(); ++it) {
		avatars_.push_back(AvatarPtr(new Avatar(*it, *this)));
	}
	addAvatars();
	//show();
}

void MainWindow::setUser(User& u)
{
   	userPtr_ = &u; 
}

MainWindow::AvatarsIter MainWindow::find(const User& u)
{
	//std::cout << "MainWindow::find()\n";
	AvatarsIter it = avatars_.begin();
	for (; it != avatars_.end(); ++it) {
		if ((*it)->getLogin() == (u.getLogin())) {
			std::cout << "it->login() == u.login()" << std::endl;
			return it;
		}
	}
	//std::cout << "after if-else in for....." << std::endl;
	//return it;
	return avatars_.end();
}


void MainWindow::showWindow()
{
	emit showSignal();
}

void MainWindow::showSlot()
{
	this->show();
}

void MainWindow::setWindowIcon()
{
	windowIcon_ = new QIcon("../resources/a.png");
	QWidget::setWindowIcon(*windowIcon_);
}

void MainWindow::sendConvRequest(const String& login)
{
	controller_.sendConvRequest(login);
}
