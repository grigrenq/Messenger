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
#include "registration.hpp"


MainWindow::MainWindow()
{
	const QSize windowSize(450,380);
	setMaximumSize(windowSize);
	setGeometry(600,400,450,380);
    setWindowTitle("Registration");	
	addLayout();
	addPushButton();
	addLineEdit();
//	addPic();
	addStatusBar();
	this->setStyleSheet("background-image: url(../back_image/b.jpeg)");
	addIcon();
}

void MainWindow::addLayout(){
	mainLayout=new QVBoxLayout();
}

void MainWindow::addPushButton()
{
	QPushButton* pb = new QPushButton("SignUp",this);
	pb->setGeometry(180,300,70,25);
	pb->setStyleSheet("QPushButton{background-color: #456ba8; color: white;}");
	QObject::connect(pb,SIGNAL(clicked()),this,SLOT(sendDetails()));
	mainLayout->addWidget(pb);
}

void MainWindow::addPic()
{
	QLabel* lb = new QLabel(this);
    lb->setGeometry(35,118,100,100);
	QPixmap* pm = new QPixmap("../addtext_com_MDM0ODA5MTk0NjA4.png");
	lb->setPixmap(*pm);
	lb->setScaledContents(true);
}

void MainWindow::addIcon()
{
	QIcon* icon = new QIcon("logo.png");
	setWindowIcon(*icon);
}

void MainWindow::addLineEdit()
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
	mainLayout->addWidget(le1);
	mainLayout->addWidget(le2);
	mainLayout->addWidget(le3);
	mainLayout->addWidget(le4);
	mainLayout->addWidget(le5);
}

void MainWindow::addStatusBar()
{
	QStatusBar* sb = new QStatusBar(this);
	sb=statusBar();
	QLabel* ql = new QLabel(sb);
}

void MainWindow::sendDetails()
{
}
