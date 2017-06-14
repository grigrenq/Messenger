#include <QWidget>
#include <QPalette>
#include<QGridLayout>
#include "Avatar.hpp"


Avatar::Avatar()
{
	setFixedSize(280,70);
	avName->setText("NameName");
	avName->setWordWrap(true);
	avName->setGeometry(10,10,100,20);
	avSurname->setText("Surname");
	avSurname->setGeometry(120,10,150,20);
	avLogin->setText("Login");
	avLogin->setGeometry(75,40,100,20);
	QPalette sample_palette;
	sample_palette.setColor(QPalette::WindowText, Qt::blue);
	avStatus->setGeometry(30,40,20,20);
	avStatus->setStyleSheet("border: 20px solid green");
	avCount->setText("5");
	avCount->setGeometry(200,40,20,20);
	avCount->setStyleSheet("border: 1px solid black");
	QGridLayout* lay=new QGridLayout;
	lay->addWidget(avName);
	lay->addWidget(avSurname);
	lay->addWidget(avLogin);
	lay->addWidget(avStatus);
	lay->addWidget(avCount);
	setStyleSheet("border:1px solid black");

}

Avatar::Avatar(user)
{
	setFixedSize(280,70);
	avName->setText(user->getName());
	avName->setWordWrap(true);
	avName->setGeometry(10,10,100,20);
	avSurname->setText(user->getSurname());
	avSurname->setGeometry(120,10,150,20);
	avLogin->setText(user->getLogin());
	avLogin->setGeometry(75,40,100,20);
	QPalette sample_palette;
	sample_palette.setColor(QPalette::WindowText, Qt::blue);
	avStatus->setGeometry(30,40,20,20);
	if(user.getStatus() == true)
		avStatus->setStyleSheet("border: 20px solid green");
	else
		avStatus->setStyleSheet("border: 20px solid red");
	avCount->setText(user->getUnreadMessagesCount().toStdString());
	avCount->setGeometry(200,40,20,20);
	avCount->setStyleSheet("border: 1px solid black");
	QGridLayout* lay=new QGridLayout;
	lay->addWidget(avName);
	lay->addWidget(avSurname);
	lay->addWidget(avLogin);
	lay->addWidget(avStatus);
	lay->addWidget(avCount);
	setStyleSheet("border:1px solid black");
	QObject::connect(this,SIGNAL(clicked()),this,SLOT(openConversation()));
}

Avatar::openConversation()
{
	MessageBox::setUser(user);
	WriteBox::setLogin(user->getLogin());
	MainWindow::updateMainWindow(user);
}


