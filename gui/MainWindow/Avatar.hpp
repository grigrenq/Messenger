#ifndef AVATAR_HPP
#define AVATAR_HPP

#include <Qt>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>


#include "../../core/ClientUser.hpp"

//#include "MainWindow.cpp"


class Avatar:public QLabel
{
	//Q_OBJECT

public:
	using User = ClientUser;

	Avatar();
	Avatar(User&);

	/*
public slots:
	void openConversation();
	*/

private:
	QLabel* avName=new QLabel(this);
	QLabel* avSurname=new QLabel(this);
	QLabel* avLogin=new QLabel(this);
	QLabel* avStatus=new QLabel(this);
	QLabel* avCount=new QLabel(this);
	ClientUser* user;
};

#endif
