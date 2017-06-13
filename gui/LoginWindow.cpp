#include "LoginWindow.hpp"
#include <iostream>
#include <QLabel>
#include <QPalette>

LoginWindow::LoginWindow()
{
    this->setGeometry(50,50,850,600);
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
    this->setLayout(m_vLayout);
    setWindowIcon();

	connectLines();
}

void LoginWindow::createLayout()
{
    m_vLayout = new QVBoxLayout();
    //m_vLayout->setContentsMargins(15, 5, 1300, 0);
    m_vLayout->addSpacing(12);
    m_vLayout->addWidget(m_loginLabel);
    m_vLayout->addWidget(m_login);
    m_vLayout->addWidget(m_passwordLabel);
    m_vLayout->addWidget(m_password);
    m_vLayout->addWidget(m_loginButton);
    m_vLayout->addWidget(m_regisButton);
    m_vLayout->addSpacerItem(new QSpacerItem(400, 400, 
                           QSizePolicy::Preferred, QSizePolicy::Expanding));
       
 //   m_vLayout->setMinimumSize(80);
//   m_vLayout->setMaximumSize(80);
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
    m_loginButton = new QPushButton("LOG IN", this);
    m_loginButton->setStyleSheet("QPushButton{background-color: #456ba8;color:white;}");
    m_loginButton->setMinimumSize(80, 20);
    m_loginButton->setMaximumSize(40, 40);
    m_regisButton = new QPushButton("CREATE NEW ACCOUNT", this);
    m_regisButton->setStyleSheet("QPushButton{background-color: #456ba8; color:white;}");
    m_regisButton->setMinimumSize(200, 20);
    m_regisButton->setMaximumSize(40, 40);
	QObject::connect(m_loginButton, SIGNAL(clicked()), this, SLOT(sendLoginReq()));
    QObject::connect(m_regisButton, SIGNAL(clicked()), this, SLOT(openRegWin()));
}

void LoginWindow::createTextEdit()
{
    m_login = new QLineEdit(this);
    m_password = new QLineEdit(this);
    m_password->setEchoMode(QLineEdit::Password);
    m_login->setMinimumHeight(30);
    m_login->setMinimumWidth(200);
    m_login->setMaximumHeight(40);
    m_login->setMaximumWidth(300);
    m_password->setMinimumHeight(30);
    m_password->setMinimumWidth(200);
    m_password->setMaximumHeight(40);
    m_password->setMaximumWidth(300);

}

void LoginWindow::createUsernameLabel()
{
    m_loginLabel = new QLabel("Login", this);
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);
    m_loginLabel->setPalette(sample_palette);
}

void LoginWindow::createPasswordLabel()
{
    m_passwordLabel = new QLabel("Password", this);
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);
    m_passwordLabel->setPalette(sample_palette);
}

void LoginWindow::setLogo()
{
    m_logo = new QLabel(this);
    m_logo->setGeometry(350, 10, 450, 450);
    QPixmap* p = new QPixmap("../resources/asd");
    m_logo->setPixmap(*p);

}

void LoginWindow::setBackground()
{
    //m_pal = new QPalette();
    m_pix = new QPixmap("../resources/b.jpeg");
    //*m_pix = m_pix->scaled(this->size(), Qt::IgnoreAspectRatio);
    QLabel *label1=new QLabel(this);
    label1->setGeometry(0,0,1700,1300);
    label1->setScaledContents(true);
    //m_pal->setBrush(QPalette::Background, *m_pix);
    label1->setPixmap(*m_pix);
    label1->setScaledContents(true);
    //this->setPalette(*m_pal);
}

void LoginWindow::setWindowIcon()
{
    m_icon = new QIcon("../resources/a.png");
    QWidget::setWindowIcon(*m_icon);
}

void LoginWindow::openRegWin()
{
    m_regWin = new RegistrationWindow();
    m_regWin->show();
}


void LoginWindow::connectLines()
{
	connect(m_login, SIGNAL(textChanged(const QString&)), this, SLOT(checkLogin(const QString&)));
	connect(m_password, SIGNAL(textChanged(const QString&)), this, SLOT(checkPassword(const QString&)));
}

void LoginWindow::checkLogin(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLoginPassword(s)) {
		//????
		m_login->setStyleSheet("border: 3px solid black");
	} else {
		std::cout << "Wrong Login.\n";
		m_login->setStyleSheet("border: 3px solid red");
	}
}
void LoginWindow::checkPassword(const QString& qs)
{
	String s = qs.toStdString();
	if (validator.checkLoginPassword(s)) {
		//????
		m_password->setStyleSheet("border: 3px solid black");
	} else {
		std::cout << "Wrong Password.\n";
		m_password->setStyleSheet("border: 3px solid red");
	}
}


void LoginWindow::sendLoginReq()
{
	String l = m_login->text().toStdString();
	if (!validator.checkLoginPassword(l)) {
		std::cout << "Wrong Login.\n";
		return;
	}
	String p = m_password->text().toStdString();
	if (!validator.checkLoginPassword(p)) {
		std::cout << "Wrong password.\n";
		return;
	}

	//..................
}
