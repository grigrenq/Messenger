#include <QWidget>
#include <QPalette>
#include <QGridLayout>
#include <QString>
#include <QFont>
#include <QEvent>

#include "MainWindow.hpp"
#include "Avatar.hpp"



Avatar::Avatar(User& u, MainWindow& mw)
	: user_(u)
	, mainWindow_(mw)
    , status_(false)
{
	avName_ = new QLabel(this);
	avSurname_ = new QLabel(this);
	avLogin_ = new QLabel(this);
	avStatus_ = new QLabel(this);
	avCount_ = new QLabel(this);
	setFixedSize(200,40);
	QFont smallFont = font();
	smallFont.setPointSize(10);
	String name = user_.getName().c_str();
	String surname = user_.getSurname().c_str();
	String nameSurname = name + " " + surname;
    status_ = user_.getStatus();
	avName_->setText(QString::fromStdString(nameSurname));
	avName_->setWordWrap(true);
	avName_->setGeometry(12,23,100,20);
	avName_->setStyleSheet("border:0px solid grey");
	avName_->setFont(smallFont);
	avName_->hide();
	QPalette* sample_palette = new QPalette();
	sample_palette->setColor(QPalette::WindowText, Qt::blue);
	avLogin_->setPalette(*sample_palette);
    status_ = user_.getStatus();
	if(user_.getStatus() == true) {
		avLogin_->setStyleSheet("border: 15px solid green;border-radius:7px");
	} else {
		avLogin_->setStyleSheet("border: 15px solid grey;border-radius:7px");
	}

	avLogin_->setText(user_.getLogin().c_str());
	avLogin_->setGeometry(10,7,150,20);
	avCount_->setText(std::to_string(user_.getUnreadMessagesCount()).c_str());
	avCount_->setGeometry(170,7,20,20);
	avCount_->setStyleSheet("border: 0.5px solid grey; border-radius:5px");
	QGridLayout* lay=new QGridLayout;
	lay->addWidget(avLogin_);
	lay->addWidget(avCount_);
	//setStyleSheet("border:1px solid black");
	
	QObject::connect(this,SIGNAL(clicked()),this,SLOT(openConversation()));
}

void Avatar::openConversation()
{
	mainWindow_.setUser(user_);
	mainWindow_.updateMessageBox();
	user_.setUnreadMessages(0);
}

void Avatar::setStatus(bool b)
{
    status_ = b;
    if(b == true) {
        avLogin_->setStyleSheet("border: 15px solid green;border-radius:7px");
    } else {
        avLogin_->setStyleSheet("border: 15px solid grey;border-radius:7px");
    }
}

void Avatar::mousePressEvent(QEvent*)
{
	emit clicked();
}

void Avatar::enterEvent(QEvent*)
{
	avName_->show();
	avSurname_->show();
}

void Avatar::leaveEvent(QEvent*)
{
	avName_->hide();
	avSurname_->hide();
}

bool Avatar::getStatus() const
{
	return status_;
}

void Avatar::incrementCount()
{
}

Avatar::String Avatar::getLogin()
{ 
	return user_.getLogin(); 
}
