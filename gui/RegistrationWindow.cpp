#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QStatusBar>
#include <QLabel>
#include <QColor>
#include <QPalette>
#include <QLabel>
#include <QPixmap>
#include <QObject>
#include <QSize>
#include <QIcon>
#include <iostream>

#include "RegistrationWindow.hpp"


RegistrationWindow::RegistrationWindow(Controller& c)
	: controller(c)
{
	const QSize windowSize(450,380);
	setMaximumSize(windowSize);
	setGeometry(600,400,450,380);
    setWindowTitle("Registration");	
	addLayout();
	addPushButton();
	addLineEdit();
	addStatusBar();
	this->setStyleSheet("background-image: url(../resources/background.jpg)");
	addIcon();
	connectLines();
}

void RegistrationWindow::addLayout(){
    m_mainLayout=new QVBoxLayout();
}

void RegistrationWindow::addPushButton()
{
	QPushButton* pb = new QPushButton("SignUp",this);
	pb->setGeometry(180,300,70,25);
	pb->setStyleSheet("QPushButton{background-color: #456ba8; color: white;}");
	QObject::connect(pb,SIGNAL(clicked()),this,SLOT(sendDetails()));
	m_mainLayout->addWidget(pb);
}

void RegistrationWindow::addPic()
{
	QLabel* lb = new QLabel(this);
    lb->setGeometry(35,118,100,100);
	QPixmap* pm = new QPixmap("addtext_com_MDM0ODA5MTk0NjA4.png");
	lb->setPixmap(*pm);
	lb->setScaledContents(true);
}

void RegistrationWindow::addIcon()
{
	QIcon* icon = new QIcon("logo.png");
	setWindowIcon(*icon);
}

void RegistrationWindow::addLineEdit()
{
	login = new QLineEdit(this);
	login->setGeometry(100,50,250,30);
	login->setPlaceholderText("Your login here...");
	QPalette p;
	p.setColor(QPalette::Background,Qt::red);
	login->setPalette(p);

	name = new QLineEdit(this);
	name->setGeometry(100,100,250,30);
	name->setPlaceholderText("Your name here...");

	surname = new QLineEdit(this);
	surname->setGeometry(100,150,250,30);
	surname->setPlaceholderText("Your surname here...");

	password1 = new QLineEdit(this);
	password1->setGeometry(100,200,250,30);
	password1->setEchoMode(QLineEdit::Password);
	password1->setPlaceholderText("Your password here...");

	password2 = new QLineEdit(this);
	password2->setGeometry(100,250,250,30);
	password2->setEchoMode(QLineEdit::Password);
	password2->setPlaceholderText("repeat password");

	m_mainLayout->addWidget(login);
	m_mainLayout->addWidget(name);
	m_mainLayout->addWidget(surname);
	m_mainLayout->addWidget(password1);
	m_mainLayout->addWidget(password2);
}



void RegistrationWindow::addStatusBar()
{
	QStatusBar* sb = new QStatusBar(this);
	sb=statusBar();
	QLabel ql(sb);
}

void RegistrationWindow::sendDetails()
{
}

void RegistrationWindow::connectLines()
{
	connect(login, SIGNAL(textChanged(const QString&)), this, SLOT(checkLogin(const QString&)));
	connect(name, SIGNAL(textChanged(const QString&)), this, SLOT(checkName(const QString&)));
	connect(surname, SIGNAL(textChanged(const QString&)), this, SLOT(checkSurname(const QString&)));
	connect(password1, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));
	connect(password2, SIGNAL(textChanged(const QString&)), this, SLOT(checkPasswords(const QString&)));
}


void RegistrationWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLoginPassword(s)) {
		//?????????
		login->setStyleSheet("border: 3px solid black");
	} else {
		//?????????
		std::cout << "Wrong Login.\n";
		login->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::checkName(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkName(s)) {
		//?????????
		name->setStyleSheet("border: 3px solid black");
	} else {
		//?????????
		std::cout << "Wrong Name.\n";
		name->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::checkSurname(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkName(s)) {
		//?????????
		surname->setStyleSheet("border: 3px solid black");
	} else {
		//?????????
		std::cout << "Wrong Surname.\n";
		surname->setStyleSheet("border: 3px solid red");
	}
}


void RegistrationWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLoginPassword(s)) {
		//?????????
		password1->setStyleSheet("border: 3px solid black");
	} else {
		//?????????
		std::cout << "Wrong password.\n";
		password1->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::checkPasswords(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkPasswords((password1->text()).toStdString(), s)) {
		//?????????
		password2->setStyleSheet("border: 3px solid black");
	} else {
		//?????????
		std::cout << "Passwords do not match.\n";
		password2->setStyleSheet("border: 3px solid red");
	}
}


