#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QIcon>
#include <QScrollBar>
#include <QScrollArea>
#include <list>
#include <string>

#include "../../core/ClientUser.hpp"

//#include "Avatar.hpp"

#include "MessageBox.hpp"
#include "WriteBox.hpp"

class Avatar;
class Controller;
#include "../../core/Controller.hpp"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	using String = Controller::String;
	using User = Controller::User;
	using Users = Controller::Users;
	using Messages = Controller::User::Messages;
	using Avatars = std::list<Avatar*>;
	using AvatarsIter = Avatars::iterator;

    MainWindow(Controller&);

	void updateMainWindow(User& u);
	void updateMainWindow(Users& users);
	void setUser(User& u);	
	void updateMessageBox();
	void sendMessage(String& msg);

	void showWindow();	//???


public slots:
	void showSlot();
	void updateSlot(User);
	void updateSlot(Users);

signals:
	void showSignal();
	void updateSignal(User);
	void updateSignal(Users);

private:
    void createLayout();
	void createLayouts();
	void addAvatar(Avatar*);
	void addAvatars();

	void updateMainWindowHelper(User&);
	void updateMainWindowHelper(Users&);
	AvatarsIter find(const User& u);

	QGridLayout *mainLayout;
    QLayout *leftSide;
    QVBoxLayout *rightSide;
	QLayout* avLay;
    QLabel *leftLabel;
    QLabel *messageLabel;
	QScrollArea *scrollArea;
	QTextEdit* messageText;
	QLayout* messageTextLayout;

	Avatars avatars;
	MessageBox *messageBox;
	WriteBox *writeBox;
	User* userPtr;
	Controller& controller;
};


#endif
