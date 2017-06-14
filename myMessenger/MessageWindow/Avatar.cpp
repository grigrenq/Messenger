//#ifndef __AVATAR__
//#define __AVATAR__

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


Avatar::Avatar(user& c,MainWindow&)
{
	avName.setText(etName());
	avName.setScaledContents(true);
	avSurname.setText(c.getSurname());
	avSurname.setScaledContents(true);
	avLogin.setText(c.getLogin());
	avLogin.setScaledContents(true);
	if(c.getStatus()==0){
		avStatus.
		}
	
	QGridLayout* lay=new QGridLayout(this);
	
}


//#define __AVATAR__

