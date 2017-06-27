#include <iostream>
#include <QScrollArea>
#include <QScrollBar>
#include <Qt>
#include <QFontMetrics>
#include <QMetaType>
#include <QIcon>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>

#include "MainWindow.hpp"
#include "Avatar.hpp"
#include "MessageBox.hpp"
#include "WriteBox.hpp"

const char delim = '%';
#include <iostream>

MainWindow::MainWindow(Controller& c)
	: mainLayout_(nullptr)
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
	, controller_(c)
	, userPtr_(nullptr)
	, messageBox_(new MessageBox(*this))
	, writeBox_(new WriteBox(*this))
{
	qRegisterMetaType<User>("User");
	qRegisterMetaType<Users>("Users");

	qRegisterMetaType<UserPtr>("UserPtr");

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
	if (messageBox_ == nullptr) {
		throw std::logic_error("messageBox  is nullptr");
	}
	if (userPtr_ != nullptr) {
		//sleep(1);
		//std::cout << "MainWindow->updateMessageBox()\n";
	   	messageBox_->update(userPtr_->getLogin(), userPtr_->getMessages());
	}
}

void MainWindow::sendMessage(String& msg)
{
	if (messageBox_ == nullptr) {
		throw std::logic_error("asdasdasd");
	}
	if(userPtr_ == nullptr) {
		return;
	}
	messageBox_->getMessageText()->verticalScrollBar()->setValue(messageBox_->getMessageText()->verticalScrollBar()->maximum());
	String toUser = (userPtr_->getLogin());
	controller_.sendMessageToUser(toUser, msg);
}

void MainWindow::updateMainWindow(User& u)
{
	emit updateSignal(u);
}

void MainWindow::updateMainWindow(Users& users)
{
	emit updateSignal(users);
}

void MainWindow::updateSlot(User u)
{
	updateMainWindowHelper(u);
}

void MainWindow::updateSlot(Users users)
{
	updateMainWindowHelper(users);
}

void MainWindow::updateMainWindowHelper(ClientUser& u)
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
			userPtr_->setUnreadMessages(0);
			messageBox_->update(u.getLogin(), u.getMessages());
		} 
	}
}

void MainWindow::updateMainWindowHelper(Users& users)
{
	avatars_.clear();
	if (avLay_ != nullptr) {
		delete avLay_;
		avLay_ = nullptr;
	}
	if (scrollWidget_ != nullptr) {
		delete scrollWidget_;
		scrollWidget_ = nullptr;
	}
	avLay_ = new QVBoxLayout();
	for (auto it = users.begin(); it != users.end(); ++it) {
		avatars_.push_back(AvatarPtr(new Avatar(*(*it), *this)));
	}
	if (userPtr_ != nullptr) {
		std::cout << "updateMainWindowHelper(users)\n";
		userPtr_->setUnreadMessages(0);
		//messageBox_->update(userPtr_->getLogin(), userPtr_->getMessages());
		updateMessageBox();
	}
	addAvatars();
}

void MainWindow::setUser(User& u)
{
	std::cout << __FUNCTION__ << std::endl;
   	userPtr_ = &u;
}

MainWindow::AvatarsIter MainWindow::find(const User& u)
{
	AvatarsIter it = avatars_.begin();
	for (; it != avatars_.end(); ++it) {
		if ((*it)->getLogin() == (u.getLogin())) {
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

void MainWindow::setWindowIcon()
{
	windowIcon_ = new QIcon("../resources/a.png");
	QWidget::setWindowIcon(*windowIcon_);
}

void MainWindow::sendConvRequest(const String& login)
{
	controller_.sendConvRequest(login);
}
