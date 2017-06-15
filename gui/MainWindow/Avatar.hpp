#ifndef AVATAR_HPP
#define AVATAR_HPP

#include <Qt>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include "../../core/ClientUser.hpp"

class MainWindow;

class Avatar : public QLabel
{
	Q_OBJECT

public:
	using User = MainWindow::User;
	using String = MainWindow::String;

	Avatar(User&, MainWindow&);
	
	void setStatus(bool);
	void incrementCount() {}
	String getLogin() { return user.getLogin(); }


public slots:
	void openConversation();

private:
	QLabel* avName=new QLabel(this);
	QLabel* avSurname=new QLabel(this);
	QLabel* avLogin=new QLabel(this);
	QLabel* avStatus=new QLabel(this);
	QLabel* avCount=new QLabel(this);
	User& user;
	MainWindow& mainWindow;
};

#endif
