#include <iostream>
#include <QLabel>
#include <QPalette>
#include <QApplication>
#include <QToolTip>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPixmap>
#include <QIcon>

#include "LoginWindow.hpp"
#include "../core/ValidationInfo.hpp"


LoginWindow::LoginWindow(Controller& c)
	: regWin(nullptr)
	, controller(c)
{
    this->setGeometry(50,50,830,500);
    this->setMinimumHeight(300);
    this->setMinimumWidth(350);
    this->setMaximumHeight(1700);
    this->setMaximumWidth(1700);

    setBackground();
    setLogo();
    createTextEdit();
    createButtons();
    createUsernameLabel();
    createPasswordLabel();
    createLayout();
    this->setLayout(vLayout);
    setWindowIcon();
    setWindowTitle("GRI-LogIn");

	connectLines();
    app->setStyleSheet("QToolTip{color: #ffffff; background-color: #990000; border: none;}");
}

void LoginWindow::createLayout()
{
    vLayout = new QVBoxLayout();
    //vLayout->setContentsMargins(15, 5, 1300, 0);
    vLayout->addSpacing(12);
    vLayout->addWidget(loginLabel);
    vLayout->addWidget(loginField);
    vLayout->addWidget(passwordLabel);
    vLayout->addWidget(passwordField);
    vLayout->addWidget(loginButton);
    vLayout->addWidget(regisButton);
    vLayout->addSpacerItem(new QSpacerItem(400, 400, QSizePolicy::Preferred, QSizePolicy::Expanding));
       
 //   vLayout_->setMinimumSize(80);
//   vLayout_->setMaximumSize(80);
    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    label1->setGeometry(15,5,50,50);
    label2->setGeometry(15,65,50,50);
    
    label1->setMinimumSize(40,50);
    label1->setMaximumSize(120,150);
    label2->setMinimumSize(50,50);
    label2->setMaximumSize(120,150);
}

void LoginWindow::createButtons()
{
    loginButton = new QPushButton("LOG IN", this);
    loginButton->setStyleSheet("QPushButton{background-color: #456ba8;color:white;}");
    loginButton->setMinimumSize(80, 20);
    loginButton->setMaximumSize(40, 40);
    regisButton = new QPushButton("CREATE NEW ACCOUNT", this);
    regisButton->setStyleSheet("QPushButton{background-color: #456ba8; color:white;}");
    regisButton->setMinimumSize(200, 20);
    regisButton->setMaximumSize(40, 40);
	QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(sendLoginReq()));
    QObject::connect(regisButton, SIGNAL(clicked()), this, SLOT(openRegWin()));
}

void LoginWindow::createTextEdit()
{
    loginField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);
    loginField->setMinimumHeight(30);
    loginField->setMinimumWidth(200);
    loginField->setMaximumHeight(40);
    loginField->setMaximumWidth(300);
    loginField->setPlaceholderText("Your login here");
    passwordField->setMinimumHeight(30);
    passwordField->setMinimumWidth(200);
    passwordField->setMaximumHeight(40);
    passwordField->setMaximumWidth(300);
    passwordField->setPlaceholderText("Your Password here");
}

void LoginWindow::createUsernameLabel()
{
    loginLabel = new QLabel("Login", this);
    QPalette samplePalette;
    samplePalette.setColor(QPalette::WindowText, Qt::white);
    loginLabel->setPalette(samplePalette);
}

void LoginWindow::createPasswordLabel()
{
    passwordLabel = new QLabel("Password", this);
    QPalette samplePalette;
    samplePalette.setColor(QPalette::WindowText, Qt::white);
    passwordLabel->setPalette(samplePalette);
}

void LoginWindow::setLogo()
{
    logo = new QLabel(this);
    logo->setGeometry(350, 10, 450, 450);
    QPixmap* p = new QPixmap("../resources/asd");
    logo->setPixmap(*p);
}

void LoginWindow::setBackground()
{
    //m_pal = new QPalette();
    pix = new QPixmap("../resources/b.jpeg");
    //*m_pix = m_pix->scaled(this->size(), Qt::IgnoreAspectRatio);
    QLabel *label1=new QLabel(this);
    label1->setGeometry(0,0,1700,1300);
    label1->setScaledContents(true);
    //m_pal->setBrush(QPalette::Background, *m_pix);
    label1->setPixmap(*pix);
    label1->setScaledContents(true);
    //this->setPalette(*m_pal);
}

void LoginWindow::setWindowIcon()
{
    icon = new QIcon("../resources/a.png");
    QWidget::setWindowIcon(*icon);
}

void LoginWindow::openRegWin()
{
	if (regWin == nullptr) {
		regWin = new RegistrationWindow(controller);
		regWin->show();
	}
}


void LoginWindow::connectLines()
{
	connect(loginField, SIGNAL(textChanged(const QString&)), this, SLOT(checkLogin(const QString&)));
	connect(passwordField, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));
	connect(this, SIGNAL(showLogSignal()), this, SLOT(showLogSlot()));
	connect(this, SIGNAL(hideLogSignal()), this, SLOT(hideLogSlot()));
	connect(this, SIGNAL(showRegSignal()), this, SLOT(showRegSlot()));
	connect(this, SIGNAL(hideRegSignal()), this, SLOT(hideRegSlot()));
}

void LoginWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLogin(s) == ValidationInfo::validLog) {
		loginField->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator.checkLogin(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(loginField->mapToGlobal(QPoint(300, -15)), "You can't use more than 20 characters");
		loginField->setStyleSheet("border: 3px solid red");
	} else if(validator.checkLogin(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(loginField->mapToGlobal(QPoint(300, -15)), "Use at least 3 characters");
		loginField->setStyleSheet("border: 3px solid red");
    } else if(validator.checkLogin(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(loginField->mapToGlobal(QPoint(300, -15)), "You can use only letters, numbers and underscore symbols");
		loginField->setStyleSheet("border: 3px solid red");
    }
}

void LoginWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkPassword(s) == ValidationInfo::validLog) {
		passwordField->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator.checkPassword(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(passwordField->mapToGlobal(QPoint(300, -15)), "You can't use more than 20 characters");
		passwordField->setStyleSheet("border: 3px solid red");
	} else if(validator.checkPassword(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(passwordField->mapToGlobal(QPoint(300, -15)), "Use at least 3 characters");
		passwordField->setStyleSheet("border: 3px solid red");
    } else if(validator.checkSurName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(passwordField->mapToGlobal(QPoint(300, -15)), "You can use only letters, numbers and underscore symbols");
		passwordField->setStyleSheet("border: 3px solid red");
    }
}
#include <iostream>
void LoginWindow::sendLoginReq()
{
	String l = loginField->text().toStdString();
	String p = passwordField->text().toStdString();

    String logRes = validator.checkLogin(l);
    String passRes = validator.checkPassword(p);
    
    if (logRes == ValidationInfo::emptyField) {
        std::cout  <<__LINE__ << std::endl;
        loginField->setPlaceholderText("You can't leave this empty");
        loginField->setStyleSheet("border: 3px solid red");
		return;
	} else if(validator.checkLogin(l) != ValidationInfo::validLog ) {
        std::cout <<  __LINE__ << std::endl;
        return;
    }

    if(passRes == ValidationInfo::emptyField){
        std::cout << __LINE__ << std::endl;
        passwordField->setPlaceholderText("You can't leave this empty");
        passwordField->setStyleSheet("border: 3px solid red");
        return;

    } else if (validator.checkPassword(p) != ValidationInfo::validLog) {
        std::cout << __LINE__ << std::endl;
		return;
	}
	controller.sendLoginRequest(l, p);
}

void LoginWindow::showLogWindow()
{
	emit showLogSignal();
}

void LoginWindow::hideLogWindow()
{
    emit hideLogSignal();
}

void LoginWindow::showRegWindow()
{
    emit showRegSignal();
}

void LoginWindow::hideRegWindow()
{
    emit hideRegSignal();
}

void LoginWindow::showRegSlot()
{
    regWin->show();
}

void LoginWindow::hideRegSlot()
{
    regWin->hide();
}

void LoginWindow::showLogSlot()
{
	this->show();
}

void LoginWindow::hideLogSlot()
{
    this->hide();
}

void LoginWindow::closeRegWindow()
{
	if (regWin != nullptr) {
		regWin->close();
		delete regWin;
		regWin = nullptr;
	}
}
