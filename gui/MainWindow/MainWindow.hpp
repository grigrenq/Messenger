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

#include "../../core/Controller.hpp"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	using User = ClientUser;
	using Users = std::list<User>;
	using String = std::string;
	using Avatars = std::list<Avatar*>;
	using AvatarsIter = Avatars::iterator;
	using Messages = std::list<String>;

    MainWindow(Controller&);
    void createLayout();
	void setUser(User& u);	
	void updateMessageBox();

private:
	void createLayouts();
	void addAvatar(Avatar*);
	void addAvatars();
	void sendMessage(String& msg);
	void updateMainWindow(User& u);
	void createAvatars(Users& users); 
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
	MessageBox messageBox;
	WriteBox writeBox;
	User* userPtr;
	Controller& controller;
};

#endif
