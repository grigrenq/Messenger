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
    bool getStatus() const;
	void incrementCount(); 
	String getLogin();

signals:
	void clicked();

public slots:
	void openConversation();

private:
	User& user_;
	MainWindow& mainWindow_;
	QLabel* avName_;
	QLabel* avSurname_;
	QLabel* avLogin_;
	QLabel* avStatus_;
	QLabel* avCount_;
    bool status_;
	int unreadMessages_;
	void mousePressEvent(QEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
};

#endif
