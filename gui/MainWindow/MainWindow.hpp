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
//#include <QIcon>
#include <QScrollBar>
#include <QScrollArea>
#include <list>
#include <string>
#include <memory>

#include "../../core/ClientUser.hpp"

//#include "Avatar.hpp"

#include "MessageBox.hpp"
#include "WriteBox.hpp"


class QIcon;
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
	using AvatarPtr = std::shared_ptr<Avatar>;
	using Avatars = std::list<AvatarPtr>;
	using AvatarsIter = Avatars::iterator;

    MainWindow(Controller&);

	void updateMainWindow(User& u);
	void updateMainWindow(Users& users);
	void setUser(User& u);	
	void updateMessageBox();
	void sendMessage(String& msg);
	void sendConvRequest(const String&);
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
	void setWindowIcon();

	void updateMainWindowHelper(User&);
	void updateMainWindowHelper(Users&);
	AvatarsIter find(const User& u);

	QGridLayout *mainLayout_;
    QLayout *leftSide_;
    QVBoxLayout *rightSide_;
	QLayout* avLay_;
    QLabel *leftLabel_;
    QLabel *messageLabel_;
	QScrollArea *scrollArea_;
	QTextEdit* messageText_;
	QLayout* messageTextLayout_;
	QIcon* windowIcon_;

	Avatars avatars_;
	Controller& controller_;
	User* userPtr_;
	MessageBox *messageBox_;
	WriteBox *writeBox_;
};


#endif
