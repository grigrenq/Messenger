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
#include "RegistrationWindow.hpp"


RegistrationWindow::RegistrationWindow()
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
	QLineEdit* le1 = new QLineEdit(this);
	le1->setGeometry(100,50,250,30);
	le1->setPlaceholderText("Your name here...");
	QPalette p;
	p.setColor(QPalette::Background,Qt::red);
	le1->setPalette(p);
	QLineEdit* le2 = new QLineEdit(this);
	le2->setGeometry(100,100,250,30);
	le2->setPlaceholderText("Your surname here...");
	QLineEdit* le3 = new QLineEdit(this);
	le3->setGeometry(100,150,250,30);
	le3->setPlaceholderText("Your login here...");
	QLineEdit* le4 = new QLineEdit(this);
	le4->setGeometry(100,200,250,30);
	le4->setEchoMode(QLineEdit::Password);
	le4->setPlaceholderText("Your password here...");
	QLineEdit* le5 = new QLineEdit(this);
	le5->setGeometry(100,250,250,30);
	le5->setEchoMode(QLineEdit::Password);
	le5->setPlaceholderText("repeat password");
	m_mainLayout->addWidget(le1);
	m_mainLayout->addWidget(le2);
	m_mainLayout->addWidget(le3);
	m_mainLayout->addWidget(le4);
	m_mainLayout->addWidget(le5);
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
