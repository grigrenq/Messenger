#include <QWidget>
#include <QPalette>
#include <QGridLayout>
#include <QString>
#include <QFont>
#include <QEvent>

#include "MainWindow.hpp"
#include "Avatar.hpp"


Avatar::Avatar(User& u, MainWindow& mw)
	: user(u)
	, mainWindow(mw)
    , status(false)
{
	avName = new QLabel(this);
	avSurname = new QLabel(this);
	avLogin = new QLabel(this);
	avStatus = new QLabel(this);
	avCount = new QLabel(this);
	setFixedSize(200,40);
	QFont smallFont = font();
	smallFont.setPointSize(10);
	std::string name = user.getName().c_str();
	std::string surname = user.getSurname().c_str();
	std::string nameSurname = name + " " + surname;
    status = user.getStatus();
	avName->setText(QString::fromStdString(nameSurname));
	avName->setWordWrap(true);
	avName->setGeometry(12,23,100,20);
	avName->setStyleSheet("border:0px solid grey");
	avName->setFont(smallFont);
	avName->hide();
	QPalette* sample_palette = new QPalette();
	sample_palette->setColor(QPalette::WindowText, Qt::blue);
	avLogin->setPalette(*sample_palette);
    status = user.getStatus();
	if(user.getStatus() == true) {
		avLogin->setStyleSheet("border: 15px solid green;border-radius:7px");
	} else {
		avLogin->setStyleSheet("border: 15px solid grey;border-radius:7px");
	}

	avLogin->setText(user.getLogin().c_str());
	avLogin->setGeometry(10,7,150,20);
	avCount->setText(std::to_string(user.getUnreadMessagesCount()).c_str());
	avCount->setGeometry(170,7,20,20);
	avCount->setStyleSheet("border: 0.5px solid grey; border-radius:5px");
	QGridLayout* lay=new QGridLayout;
	lay->addWidget(avLogin);
	lay->addWidget(avCount);
	//setStyleSheet("border:1px solid black");
	
	QObject::connect(this,SIGNAL(clicked()),this,SLOT(openConversation()));
}

void Avatar::openConversation()
{
	mainWindow.setUser(user);
	mainWindow.updateMessageBox();
}

void Avatar::setStatus(bool b)
{
    status = b;
    if(b == true) {
        avLogin->setStyleSheet("border: 15px solid green;border-radius:7px");
    } else {
        avLogin->setStyleSheet("border: 15px solid grey;border-radius:7px");
    }
}

void Avatar::mousePressEvent(QEvent*)
{
	emit clicked();
}

void Avatar::enterEvent(QEvent*)
{
	avName->show();
	avSurname->show();
}

void Avatar::leaveEvent(QEvent*)
{
	avName->hide();
	avSurname->hide();
}
