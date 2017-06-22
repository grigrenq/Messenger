#include <iostream>
#include <QLabel>
#include <QPalette>
#include <QApplication>
#include <QToolTip>

#include "LoginWindow.hpp"
#include "../core/ValidationInfo.hpp"


LoginWindow::LoginWindow(Controller& c)
	: regWin_(nullptr)
	, controller_(c)
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
    this->setLayout(vLayout_);
    setWindowIcon();

	connectLines();
    app_->setStyleSheet("QToolTip{color: #ffffff; background-color: #990000; border: none;}");
}

void LoginWindow::createLayout()
{
    vLayout_ = new QVBoxLayout();
    //vLayout_->setContentsMargins(15, 5, 1300, 0);
    vLayout_->addSpacing(12);
    vLayout_->addWidget(loginLabel_);
    vLayout_->addWidget(login_);
    vLayout_->addWidget(passwordLabel_);
    vLayout_->addWidget(password_);
    vLayout_->addWidget(loginButton_);
    vLayout_->addWidget(regisButton_);
    vLayout_->addSpacerItem(new QSpacerItem(400, 400, 
                           QSizePolicy::Preferred, QSizePolicy::Expanding));
       
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
    loginButton_ = new QPushButton("LOG IN", this);
    loginButton_->setStyleSheet("QPushButton{background-color: #456ba8;color:white;}");
    loginButton_->setMinimumSize(80, 20);
    loginButton_->setMaximumSize(40, 40);
    regisButton_ = new QPushButton("CREATE NEW ACCOUNT", this);
    regisButton_->setStyleSheet("QPushButton{background-color: #456ba8; color:white;}");
    regisButton_->setMinimumSize(200, 20);
    regisButton_->setMaximumSize(40, 40);
	QObject::connect(loginButton_, SIGNAL(clicked()), this, SLOT(sendLoginReq()));
    QObject::connect(regisButton_, SIGNAL(clicked()), this, SLOT(openRegWin()));
}

void LoginWindow::createTextEdit()
{
    login_ = new QLineEdit(this);
    password_ = new QLineEdit(this);
    password_->setEchoMode(QLineEdit::Password);
    login_->setMinimumHeight(30);
    login_->setMinimumWidth(200);
    login_->setMaximumHeight(40);
    login_->setMaximumWidth(300);
    login_->setPlaceholderText("Your login here...");
    password_->setMinimumHeight(30);
    password_->setMinimumWidth(200);
    password_->setMaximumHeight(40);
    password_->setMaximumWidth(300);
    password_->setPlaceholderText("Your password here...");

}

void LoginWindow::createUsernameLabel()
{
    loginLabel_ = new QLabel("Login", this);
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);
    loginLabel_->setPalette(sample_palette);
}

void LoginWindow::createPasswordLabel()
{
    passwordLabel_ = new QLabel("Password", this);
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);
    passwordLabel_->setPalette(sample_palette);
}

void LoginWindow::setLogo()
{
    logo_ = new QLabel(this);
    logo_->setGeometry(350, 20, 450, 450);
    QPixmap* p = new QPixmap("../resources/asd");
    logo_->setPixmap(*p);

}

void LoginWindow::setBackground()
{
    //m_pal = new QPalette();
    pix_ = new QPixmap("../resources/b.jpeg");
    //*pix_ = m_pix->scaled(this->size(), Qt::IgnoreAspectRatio);
    QLabel *label1=new QLabel(this);
    label1->setGeometry(0,0,1700,1300);
    label1->setScaledContents(true);
    //m_pal->setBrush(QPalette::Background, *pix_);
    label1->setPixmap(*pix_);
    label1->setScaledContents(true);
    //this->setPalette(*m_pal);
}

void LoginWindow::setWindowIcon()
{
    icon_ = new QIcon("../resources/a.png");
    QWidget::setWindowIcon(*icon_);
}

void LoginWindow::openRegWin()
{
	regWin_ = new RegistrationWindow(controller_);
	regWin_->show();
}


void LoginWindow::connectLines()
{
	connect(login_, SIGNAL(textChanged(const QString&)), this, SLOT(checkLogin(const QString&)));
	connect(password_, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));
	connect(this, SIGNAL(showSignal()), this, SLOT(showSlot()));
}

void LoginWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator_.checkLogin(s) == ValidationInfo::validLog) {
		login_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator_.checkLogin(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(login_->mapToGlobal(QPoint(300, -15)), "You can't use more than 20 characters");
		login_->setStyleSheet("border: 3px solid red");
	} else if(validator_.checkLogin(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(login_->mapToGlobal(QPoint(300, -15)), "Use at least 3 characters");
		login_->setStyleSheet("border: 3px solid red");
    } else if(validator_.checkLogin(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(login_->mapToGlobal(QPoint(300, -15)), "You can use only letters, numbers and underscore symbols");
		login_->setStyleSheet("border: 3px solid red");
    }
}

void LoginWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator_.checkPassword(s) == ValidationInfo::validLog) {
		password_->setStyleSheet("border: 3px solid black");
		QToolTip::hideText();
	} else if(validator_.checkPassword(s) == ValidationInfo::validMaxLength) {
        QToolTip::showText(password_->mapToGlobal(QPoint(300, -15)), "You can't use more than 20 characters");
		password_->setStyleSheet("border: 3px solid red");
	} else if(validator_.checkPassword(s) == ValidationInfo::validMinLength) {
        QToolTip::showText(password_->mapToGlobal(QPoint(300, -15)), "Use at least 5 characters");
		password_->setStyleSheet("border: 3px solid red");
    } else if(validator_.checkSurName(s) == ValidationInfo::invalidSymbol) {
        QToolTip::showText(password_->mapToGlobal(QPoint(300, -15)), "You can use only letters, numbers and underscore symbols");
		password_->setStyleSheet("border: 3px solid red");
    }
}

void LoginWindow::sendLoginReq()
{
	String l = login_->text().toStdString();
	String p = password_->text().toStdString();

    String logRes = validator_.checkLogin(l);
    String passRes = validator_.checkPassword(p);
    
    if (logRes == ValidationInfo::emptyField) {
        login_->setPlaceholderText("You can't leave this empty");
        login_->setStyleSheet("border: 3px solid red");
		return;
	} else if(validator_.checkLogin(l) != ValidationInfo::validLog ) {
        return;
    }
    
    if(passRes == ValidationInfo::emptyField){
        password_->setPlaceholderText("You can't leave this empty");
        password_->setStyleSheet("border: 3px solid red");
        return;

    } else if (validator_.checkPassword(p) != ValidationInfo::validLog) {
		return;
	}
	controller_.sendLoginRequest(l, p);
}

void LoginWindow::showWindow()
{
	emit showSignal();
}

void LoginWindow::showSlot()
{
	this->show();
}

void LoginWindow::closeRegWindow()
{
	if (regWin_ != nullptr) {
		regWin_->close();
		delete regWin_;
		regWin_ = nullptr;
	}
}
