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

#include "MessageBox.hpp"
#include "WriteBox.hpp"
#include "Avatar.hpp"
#include "../../core/ClientUser.hpp"
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
	//using Messages = std::list<String>;

    MainWindow();
    void createLayout();

private:
	void createLayouts();
	void addAvatar(Avatar*);
	void addAvatars();

	void updateMessageBox() { messageBox.update(userPtr->getLogin(), userPtr->getMessages()); }
	void sendMessage(String& toUser, String& msg)
	{
		controller.sendMessageToUser(toUser, msg);
		userPtr->addMessage(controller.getLogin(),msg);
		messageBox.update(userPtr->getMessages());
	}
	void updateMainWindow(User& u)
	{
		auto it = find(u);
		if (it == Avatars.end()) {
			Avatars.push_back(new Avatar(u));
			addAvatar(Avatars.back());
		} else {
			(*it)->setStatus(u.getStatus());
			if (userPtr->getLogin() == u.getLogin()) {
				messageBox.update(u.getLogin(), u.getMessages());
			} else {
				(*it)->incrementCount();
			}
		}
	}
	void setUser(User& u) { userPtr = &u; }
	void createAvatars(Users& users) 
	{
		for (auto it = users.begin(), it != users.end(); ++it) {
			avatars.push_back(new Avatar(*it));
		}
		addAvatars();
		//show();
	}

	AvatarsIter find(const User& u)
	{
		AvatarsIter it;
		for (; it != avatars.end(); ++it) {
			if ((*it)->getLogin() == u.getLogin()) {
				return it;
			}
		}
		return it;
	}

    QGridLayout *mainLayout;
    QLayout *leftSide;
    QVBoxLayout *rightSide;
	QLayout* avLay;
    QLabel *leftLabel;
    QLabel *messageLabel;
	QScrollArea *scrollArea;
	QTextEdit* messageText;
	QLayout* messageTextLayout;

	QTextEdit *textEdit;
	QPushButton *sendButton;

	Avatars avatars;
	MessageBox messageBox;
	WriteBox writeBox;
	User* userPtr;
	Controller& controller;
};
