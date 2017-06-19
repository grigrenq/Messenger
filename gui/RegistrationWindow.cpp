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
#include <QToolTip>

#include "RegistrationWindow.hpp"
#include "../core/ValidationInfo.hpp"


RegistrationWindow::RegistrationWindow(Controller& c)
	: controller(c)
{
	const QSize windowSize(450,380);
	setMaximumSize(windowSize);
	setGeometry(600,400,450,380);
	this->setStyleSheet("background-image: url(../resources/background.jpg)");
	setWindowTitle("Registration");	
	addLayout();
	addPushButton();
	addLineEdit();
	addStatusBar();
	addIcon();
	connectLines();
    setToolTip();
}

void RegistrationWindow::addLayout(){
	m_mainLayout=new QVBoxLayout();
}

void RegistrationWindow::addPushButton()
{
	signUp = new QPushButton("SignUp",this);
	signUp->setGeometry(180,300,70,25);
	signUp->setStyleSheet("QPushButton{background-color: #456ba8; color: white;}");
	m_mainLayout->addWidget(signUp);
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
	//login->setPalette(p);

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

void RegistrationWindow::connectLines()
{
	connect(login, SIGNAL(textChanged(const QString&)), this, SLOT(checkLogin(const QString&)));
	connect(name, SIGNAL(textChanged(const QString&)), this, SLOT(checkName(const QString&)));
	connect(surname, SIGNAL(textChanged(const QString&)), this, SLOT(checkSurname(const QString&)));
	connect(password1, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));
	connect(password2, SIGNAL(textChanged(const QString&)), this, SLOT(checkPasswords(const QString&)));

	connect(signUp, SIGNAL(clicked()), this, SLOT(sendRegistrationReq()));
}

void RegistrationWindow::setTipColor()
{
    palette = QToolTip::palette();
    palette.setColor(QPalette::ToolTipBase,Qt::red);
    palette.setColor(QPalette::ToolTipText,Qt::red);//dark grey for text
    QToolTip::setPalette(palette);
}

void RegistrationWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLogin(s)) {
		login->setStyleSheet("border: 3px solid black");
	} else {
        QToolTip::showText(login->mapToGlobal(QPoint(250, 0)), "Login or password must contain only esim incher\n");
		login->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::checkName(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkName(s) == "") {
		name->setStyleSheet("border: 3px solid black");
	} else if(validator.checkName(s) == ValidationInfo::validMaxLength){
        QToolTip::showText(name->mapToGlobal(QPoint(250, 0)), "The name is too long\n");
		name->setStyleSheet("border: 3px solid red");
	} else if(validator.checkName(s) == ValidationInfo::validMinLength){
        QToolTip::showText(name->mapToGlobal(QPoint(250, 0)), "The name is too short\n");
        name->setStyleSheet("border: 3px solid red");
    }
    else {
        name->setToolTip();
        QToolTip::showText(name->mapToGlobal(QPoint(250, 0)), "Name and Surname must cotain inch vor baner\n");
        name->setStyleSheet("border: 3px solid red");
    }
}

void RegistrationWindow::checkSurname(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkSurname(s) == "") {
		surname->setStyleSheet("border: 3px solid black");
	} else if(validator.checkSurname(s) == ValidationInfo::validMaxLength){
        QToolTip::showText(surname->maptoGlobal(QPoint(250, 0)), "Surname is tooooo long");
		surname->setStyleSheet("border: 3px solid red");
	} else if(validator.checkSurname(s) == ValidationInfo::validMinLength){
        QToolTip::showText(surname->maptoGlobal(QPoint(250, 0)), "Surname is tooooo short");
        surname->setStyleSheet("border: 3px solid red");
    }
    else {
        std::cout << "checkIsNotAlpha" <<std::endl;// must be changed
        surname->setStyleSheet("border: 3px solid red");
    }
}


void RegistrationWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkPassword(s)) {
		password1->setStyleSheet("border: 3px solid black");
	} else {
        QToolTip::showText(password1->mapToGlobal(QPoint(250, 0)), "login or password must contain only characters, numbers and underscore\n");
		password1->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::checkPasswords(const QString& qs)
{
	String p1 = password1->text().toStdString();
	String p2 = qs.toStdString();

	if (validator.checkPasswords(p1, p2)) {

		password2->setStyleSheet("border: 3px solid black");
	} else {
        QToolTip::showText(password2->mapToGlobal(QPoint(250, 0)), "Passwords does not match");
        passwor2->setToolTip("passwords does not match");
        password2->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::sendRegistrationReq()
{
	String l = login->text().toStdString();
	String n = name->text().toStdString();
	String sn = surname->text().toStdString();
	String p1 = password1->text().toStdString();
	String p2 = password2->text().toStdString();

	if (validator.checkLogin(l)) {

		return;
	}
	if (validator.checkName(n) == "") {

		return;
	}
	if (validator.checkSurName(sn) == "") {

		return;
	}
	if (validator.checkPassword(p1)) {

		return;
	}
	if (validator.checkPasswords(p1, p2)) {

		return;
	}
	controller.sendRegistrationRequest(l, n, sn, p1);
}

