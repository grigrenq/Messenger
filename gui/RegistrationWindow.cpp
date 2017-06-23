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
	: controller_(c)
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
    app_->setStyleSheet("QToolTip{color: #ffffff; background-color: #990000; border: none;}");
}

void RegistrationWindow::setBackground()
{
    pix_ = new QPixmap("../resources/background.jpg");
    QLabel *label1 = new QLabel(this);
    label1->setGeometry(0,0,450,380);
    label1->setScaledContents(true);
    label1->setPixmap(*pix_);
}

void RegistrationWindow::addLayout(){
	mainLayout_=new QVBoxLayout();
}

void RegistrationWindow::addPushButton()
{
	signUp_ = new QPushButton("SignUp",this);
	signUp_->setGeometry(180,300,70,25);
	signUp_->setStyleSheet("QPushButton{background-color: #456ba8; color: white;}");
	mainLayout_->addWidget(signUp_);
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
	login_ = new QLineEdit(this);
	login_->setGeometry(100,50,250,30);
	login_->setPlaceholderText("Your login here...");
	QPalette p;
	p.setColor(QPalette::Background,Qt::red);
	//login->setPalette(p);

	name_ = new QLineEdit(this);
	name_->setGeometry(100,100,250,30);
	name_->setPlaceholderText("Your name here...");

	surname_ = new QLineEdit(this);
	surname_->setGeometry(100,150,250,30);
	surname_->setPlaceholderText("Your surname here...");

	password1_ = new QLineEdit(this);
	password1_->setGeometry(100,200,250,30);
	password1_->setEchoMode(QLineEdit::Password);
	password1_->setPlaceholderText("Your password here...");

	password2_ = new QLineEdit(this);
	password2_->setGeometry(100,250,250,30);
	password2_->setEchoMode(QLineEdit::Password);
	password2_->setPlaceholderText("Repeat password here...");

	mainLayout_->addWidget(login_);
	mainLayout_->addWidget(name_);
	mainLayout_->addWidget(surname_);
	mainLayout_->addWidget(password1_);
	mainLayout_->addWidget(password2_);
}

/*void RegistrationWindow::addStatusBar()
{
	QStatusBar* sb = new QStatusBar(this);
	sb=statusBar();
	QLabel ql(sb);
}*/

void RegistrationWindow::connectLines()
{
	connect(login_, SIGNAL(textChanged(const QString&)), this, SLOT(checkLogin(const QString&)));
	connect(name_, SIGNAL(textChanged(const QString&)), this, SLOT(checkName(const QString&)));
	connect(surname_, SIGNAL(textChanged(const QString&)), this, SLOT(checkSurname(const QString&)));
	connect(password1_, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));
	connect(password2_, SIGNAL(textChanged(const QString&)), this, SLOT(checkPasswords(const QString&)));

	connect(signUp_, SIGNAL(clicked()), this, SLOT(sendRegistrationReq()));
}

void RegistrationWindow::setTipColor()
{
    palette_ = QToolTip::palette();
    palette_.setColor(QPalette::ToolTipBase,Qt::red);
    palette_.setColor(QPalette::ToolTipText,Qt::red);
    QToolTip::setPalette(palette_);
}

void RegistrationWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator_.checkLogin(s) == ValidationInfo::validLog) {
		login_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator_.checkLogin(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(login_->mapToGlobal(QPoint(250, -15)), "You can't use more than 20 characters");
		login_->setStyleSheet("border: 3px solid red");
	} else if(validator_.checkLogin(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(login_->mapToGlobal(QPoint(250, -15)), "Use at least 3 characters");
		login_->setStyleSheet("border: 3px solid red");
    } else if(validator_.checkLogin(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(login_->mapToGlobal(QPoint(250, -15)), "You can use only letters, numbers and underscore symbols");
		login_->setStyleSheet("border: 3px solid red");
    }
}

void RegistrationWindow::checkName(const QString& qs)
{
	String s = qs.toStdString();
	if (validator_.checkName(s) == ValidationInfo::validName) {
		name_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator_.checkName(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(name_->mapToGlobal(QPoint(250, -15)), "You can't use more than 20 characters");
		name_->setStyleSheet("border: 3px solid red");
	} else if(validator_.checkName(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(name_->mapToGlobal(QPoint(250, -15)), "Use at least 3 characters");
        name_->setStyleSheet("border: 3px solid red");
    } else if(validator_.checkName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(name_->mapToGlobal(QPoint(250, -15)), "You can use only letters");
        name_->setStyleSheet("border: 3px solid red");
    }
}

void RegistrationWindow::checkSurname(const QString& qs)
{
	String s = qs.toStdString();
	if (validator_.checkSurName(s) == ValidationInfo::validName) {
		surname_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator_.checkSurName(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(surname_->mapToGlobal(QPoint(250, -15)), "You can't use more than 20 characters");
		surname_->setStyleSheet("border: 3px solid red");
	} else if(validator_.checkSurName(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(surname_->mapToGlobal(QPoint(250, -15)), "Use at least 3 characters");
        surname_->setStyleSheet("border: 3px solid red");
    } else if(validator_.checkSurName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(surname_->mapToGlobal(QPoint(250, -15)), "You can use only letters");
        surname_->setStyleSheet("border: 3px solid red");
    }
}


void RegistrationWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator_.checkPassword(s) == ValidationInfo::validLog) {
		password1_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator_.checkPassword(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(password1_->mapToGlobal(QPoint(250, -15)), "You can't use more than 20 characters");
		password1_->setStyleSheet("border: 3px solid red");
	} else if(validator_.checkPassword(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(password1_->mapToGlobal(QPoint(250, -15)), "Use at least 5 characters");
		password1_->setStyleSheet("border: 3px solid red");
    } else if(validator_.checkSurName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(password1_->mapToGlobal(QPoint(250, -15)), "You can use only letters, numbers and underscore symbols");
		password1_->setStyleSheet("border: 3px solid red");
    }
}

void RegistrationWindow::checkPasswords(const QString& qs)
{
	String p1 = password1_->text().toStdString();
	String p2 = qs.toStdString();

	if (validator_.checkPasswords(p1, p2)) {
		password2_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else {
        QToolTip::showText(password2_->mapToGlobal(QPoint(250, -15)), "These passwords don't match, Try again");
        password2_->setStyleSheet("border: 3px solid red");
	}
}

void RegistrationWindow::sendRegistrationReq()
{
	String l = login_->text().toStdString();
	String n = name_->text().toStdString();
	String sn = surname_->text().toStdString();
	String p1 = password1_->text().toStdString();
	String p2 = password2_->text().toStdString();
    
    String logRes = validator_.checkLogin(l);
    String passRes = validator_.checkPassword(p1);
    String nameRes = validator_.checkName(n);
    String surnameRes = validator_.checkSurName(sn);
    String passRes2 = validator_.checkPassword(p2);

	if (logRes == ValidationInfo::emptyField) {
        login_->setPlaceholderText("You can't leave this empty");
        login_->setStyleSheet("border: 3px solid red");
		return;
	} else if(validator_.checkLogin(l) != ValidationInfo::validLog ) {
        return;
    }

    if(nameRes == ValidationInfo::emptyField) {
        name_->setPlaceholderText("You can't leave this empty");
        name_->setStyleSheet("border: 3px solid red");
        return;
    } else if (validator_.checkName(n) != ValidationInfo::validName) {
		return;
	}

    if(surnameRes == ValidationInfo::emptyField) {
        surname_->setPlaceholderText("You can't leave this empty");
        surname_->setStyleSheet("border: 3px solid red");
        return;
    } else if (validator_.checkSurName(sn) != ValidationInfo::validName) {
		return;
	}

    if(passRes == ValidationInfo::emptyField){
        password1_->setPlaceholderText("You can't leave this empty");
        password1_->setStyleSheet("border: 3px solid red");
        return;

    } else if (validator_.checkPassword(p1) != ValidationInfo::validLog) {
		return;
	}
    
    if(passRes2 == ValidationInfo::emptyField){
        password2_->setPlaceholderText("You can't leave this empty");
        password2_->setStyleSheet("border: 3px solid red");
        return;

    } else if (validator_.checkPassword(p2) != ValidationInfo::validLog) {
		return;
	}
    

	if (!validator_.checkPasswords(p1, p2)) {
		return;
	}
	controller_.sendRegistrationRequest(l, n, sn, p1);
    this->hide();
}

