#include <QWidget>
#include <QPalette>
#include <QGridLayout>
#include <QString>
#include "MainWindow.hpp"
#include "Avatar.hpp"
//#include "MainWindow.hpp"



/*Avatar::Avatar()
	: user(nullptr)
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
*/
Avatar::Avatar(User& u, MainWindow& mw)
	: user(u)
	  , mainWindow(mw)
{
	setFixedSize(200,40);
	QFont smallFont = font();
	smallFont.setPointSize(10);
	std::string name = user.getName().c_str();
	std::string surname = user.getSurname().c_str();
	std::string nameSurname = name + " " + surname;
	avName->setText(QString::fromStdString(nameSurname));
	avName->setWordWrap(true);
	avName->setGeometry(12,23,100,20);
	avName->setStyleSheet("border:0px solid grey");
	avName->setFont(smallFont);
	avName->hide();
	QPalette* sample_palette;
	sample_palette->setColor(QPalette::WindowText, Qt::blue);
	avLogin->setPalette(*sample_palette);
	if(user.getStatus() == true)
		avLogin->setStyleSheet("border: 15px solid green;border-radius:7px");
	else
		avLogin->setStyleSheet("border: 15px solid grey;border-radius:7px");
	avLogin->setText(user.getLogin().c_str());
	avLogin->setGeometry(10,7,150,20);
	avCount->setText(std::to_string(user.getUnreadMessagesCount()).c_str());
	avCount->setGeometry(170,7,20,20);
	avCount->setStyleSheet("border: 0.5px solid grey; border-radius:5px");
	QGridLayout* lay=new QGridLayout;
	lay->addWidget(avLogin);
	lay->addWidget(avCount);
	setStyleSheet("border:1px solid black");
	QObject::connect(this,SIGNAL(clicked()),this,SLOT(openConversation()));
}

void Avatar::openConversation()
{
	mainWindow.setUser(user);
	mainWindow.updateMessageBox();
}

void Avatar::setStatus(bool)
{
}

