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
#include <QApplication>
#include "RegistrationWindow.hpp"
#include "../core/ValidationInfo.hpp"


RegistrationWindow::RegistrationWindow(Controller& c)
	: controller(c)
{
	const QSize windowSize(450,380);
	setMaximumSize(windowSize);
	setGeometry(600,400,450,380);
	//this->setStyleSheet("background-image: url(../resources/background.jpg)");
    setBackground();
	setWindowTitle("Registration");	
	addLayout();
	addPushButton();
	addLineEdit();
	addIcon();
	connectLines();
    setTipColor();
}

void RegistrationWindow::setBackground()
{
    m_pix = new QPixmap("../resources/background.jpg");
    QLabel *label1 = new QLabel(this);
    label1->setGeometry(0,0,450,380);
    label1->setScaledContents(true);
    label1->setPixmap(*m_pix);
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



/*void RegistrationWindow::addStatusBar()
{
	QStatusBar* sb = new QStatusBar(this);
	sb=statusBar();
	QLabel ql(sb);
}*/

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
    palette.setColor(QPalette::ToolTipText,Qt::red);
    QToolTip::setPalette(palette);
}

void RegistrationWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLogin(s) == ValidationInfo::validLog) {
		login->setStyleSheet("border: 3px solid black");
	} else if(validator.checkLogin(s) == ValidationInfo::validMaxLength) {
        QApplication* app;
        app->setStyleSheet("QToolTip{color: #ffffff; background-color: #990000; border: none;}");
        QToolTip::showText(login->mapToGlobal(QPoint(250, -15)), "You can't use more than 20 charactrs");
		login->setStyleSheet("border: 3px solid red");
	} else if(validator.checkLogin(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(login->mapToGlobal(QPoint(250, -15)), "Use at least 5 charactrs");
		login->setStyleSheet("border: 3px solid red");
    } else if(validator.checkLogin(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(login->mapToGlobal(QPoint(250, -15)), "You can use only letters, numbers and underscore symbols");
		login->setStyleSheet("border: 3px solid red");
    }
}

void RegistrationWindow::checkName(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkName(s) == ValidationInfo::validName) {
		name->setStyleSheet("border: 3px solid black");
	} else if(validator.checkName(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(name->mapToGlobal(QPoint(250, -15)), "You can't use more than 20 characters");
		name->setStyleSheet("border: 3px solid red");
	} else if(validator.checkName(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(name->mapToGlobal(QPoint(250, -15)), "Use at least 5 characters");
        name->setStyleSheet("border: 3px solid red");
    } else if(validator.checkName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(name->mapToGlobal(QPoint(250, -15)), "You can use only letters");
        name->setStyleSheet("border: 3px solid red");
    }
}

void RegistrationWindow::checkSurname(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkSurName(s) == ValidationInfo::validName) {
		surname->setStyleSheet("border: 3px solid black");
	} else if(validator.checkSurName(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(surname->mapToGlobal(QPoint(250, -15)), "Surname is tooooo long");
		surname->setStyleSheet("border: 3px solid red");
	} else if(validator.checkSurName(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(surname->mapToGlobal(QPoint(250, -15)), "Surname is tooooo short");
        surname->setStyleSheet("border: 3px solid red");
    } else if(validator.checkSurName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(surname->mapToGlobal(QPoint(250, -15)), "Name and Surname must cotain inch vor baner");
        surname->setStyleSheet("border: 3px solid red");
    }
}


void RegistrationWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkPassword(s) == ValidationInfo::validLog) {
		password1->setStyleSheet("border: 3px solid black");
	} else if(validator.checkPassword(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(password1->mapToGlobal(QPoint(250, -15)), "You can't use more than characters");
		password1->setStyleSheet("border: 3px solid red");
	} else if(validator.checkPassword(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(password1->mapToGlobal(QPoint(250, -15)), "use at least 5 characters");
		password1->setStyleSheet("border: 3px solid red");
    } else if(validator.checkSurName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(password1->mapToGlobal(QPoint(250, -15)), "You can use only letters, numbers and underscore simbols");
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
        QToolTip::showText(password2->mapToGlobal(QPoint(250, -15)), "These passwords don't match, Try again");
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
    
    String logRes = validator.checkLogin(l);
    String passRes = validator.checkPassword(p1);
    String nameRes = validator.checkName(n);
    String surnameRes = validator.checkSurName(sn);
    String passRes2 = validator.checkPassword(p2);

	if (logRes == ValidationInfo::emptyField) {
        login->setPlaceholderText("You can't leave this empty");
        login->setStyleSheet("border: 3px solid red");
		return;
	} else if(validator.checkLogin(l) != ValidationInfo::validLog ) {
        return;
    }

    if(nameRes == ValidationInfo::emptyField) {
        name->setPlaceholderText("You can't leave this empty");
        name->setStyleSheet("border: 3px solid red");
        return;
    } else if (validator.checkName(n) != ValidationInfo::validName) {
		return;
	}

    if(surnameRes == ValidationInfo::emptyField) {
        surname->setPlaceholderText("You can't leave this empty");
        surname->setStyleSheet("border: 3px solid red");
        return;
    } else if (validator.checkSurName(sn) != ValidationInfo::validName) {
		return;
	}

    if(passRes == ValidationInfo::emptyField){
        password1->setPlaceholderText("You can't leave this empty");
        password1->setStyleSheet("border: 3px solid red");
        return;

    } else if (validator.checkPassword(p1) != ValidationInfo::validLog) {
		return;
	}
    
    if(passRes2 == ValidationInfo::emptyField){
        password2->setPlaceholderText("You can't leave this empty");
        password2->setStyleSheet("border: 3px solid red");
        return;

    } else if (validator.checkPassword(p2) != ValidationInfo::validLog) {
		return;
	}
    

	if (!validator.checkPasswords(p1, p2)) {
		return;
	}
	controller.sendRegistrationRequest(l, n, sn, p1);
    this->hide();
}

