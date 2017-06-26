#include <QWidget>
#include <QPalette>
#include <QGridLayout>
#include <QString>
#include <QFont>

#include "MainWindow.hpp"
#include "Avatar.hpp"

Avatar::Avatar(User& u, MainWindow& mw)
	: user_(u)
	, mainWindow_(mw)
	, avName_(nullptr)
	, avSurname_(nullptr)
	, avLogin_(nullptr)
	, avStatus_(nullptr)
	, avCount_(nullptr) 
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
	String name = user_.getName();
	String surname = user_.getSurname();
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
		avLogin_->setStyleSheet("border: 15px solid green;border-radius:7px; color: white");
	} else {
		avLogin_->setStyleSheet("border: 15px solid grey;border-radius:7px; color: white");
	}

	avLogin_->setText(QString::fromStdString(user_.getLogin()));
	avLogin_->setGeometry(10,7,150,20);
	avCount_->setText(QString::fromStdString(std::to_string(user_.getUnreadMessagesCount())));
	avCount_->setGeometry(170,7,20,20);
	avCount_->setStyleSheet("border: 0.5px solid grey; border-radius:5px");
	QGridLayout* lay=new QGridLayout;
	lay->addWidget(avLogin_);
	lay->addWidget(avCount_);
	setStyleSheet("border:1px solid black");
	
	QObject::connect(this,SIGNAL(clicked()),this,SLOT(openConversation()));
}

void Avatar::openConversation()
{
	std::cout << __FUNCTION__ << std::endl;
	//std::cout << "before setUser-";
	std::cout <<  user_.getLogin() << std::endl;
	std::cout << "Setting user to " << user_.getLogin() << ".\n";
	mainWindow_.setUser(user_);
	mainWindow_.sendConvRequest(user_.getLogin());
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

void Avatar::mousePressEvent(QMouseEvent*)
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

const char* Avatar::getLogin(int)
{
	//std::cout << __FUNCTION__ << std::endl;
	//return "some string\n";
	return user_.getLogin().c_str();
	//std::cout << __FUNCTION__ << std::endl;	
}

Avatar::String Avatar::getLogin()
{
	return user_.getLogin();
}

