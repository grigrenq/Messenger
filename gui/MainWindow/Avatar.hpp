#ifndef AVATAR_HPP
#define AVATAR_HPP

#include <Qt>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <MainWindow.hpp>
#include <QEvent>
#include "../../core/ClientUser.hpp"

class MainWindow;
class QEvent;

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


signals:
	void clicked();

public slots:
	void openConversation();

private:
	QLabel* avName;
	QLabel* avSurname;
	QLabel* avLogin;
	QLabel* avStatus;
	QLabel* avCount;
	User& user;
	MainWindow& mainWindow;
	void mousePressEvent(QEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
};

#endif
