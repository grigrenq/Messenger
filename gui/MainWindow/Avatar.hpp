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
    bool getStatus() const { return status; }
	void incrementCount() 
	{
	}
	String getLogin() { return user.getLogin(); }


signals:
	void clicked();

public slots:
	void openConversation();

private:
	User& user;
	MainWindow& mainWindow;
	QLabel* avName;
	QLabel* avSurname;
	QLabel* avLogin;
	QLabel* avStatus;
	QLabel* avCount;
    bool status;
	int unreadMessages;
	void mousePressEvent(QEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
};

#endif
