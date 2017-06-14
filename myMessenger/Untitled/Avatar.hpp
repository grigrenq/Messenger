#ifndef __Avatar_hpp
#define __Avatar_hpp

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <ClientUser.hpp>
#include <MessageBox.cpp>
#include <WriteBox.cpp>
#include <MainWindow.cpp>
#include <Qt>

class Avatar:public QLabel
{
	Q_OBJECT
private:
	QLabel* avName=new QLabel(this);
	QLabel* avSurname=new QLabel(this);
	QLabel* avLogin=new QLabel(this);
	QLabel* avStatus=new QLabel(this);
	QLabel* avCount=new QLabel(this);
	ClientUser* user;
public:
	Avatar();
	Avatar(CLientUser&);
public slots:
	void openConversation();
};

#endif//__Avatar_hpp
