#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <string>
#include <list>
#include <QVBoxLayout>
#include <QTextEdit>
#include "../../core/ClientUser.hpp"

class QLayout;
class QTextEdit;

class MainWindow;
class MessageBox
{
public:
	using User = ClientUser;
	using Messages = std::list<std::string>;
	using String = ClientUser::String;
	//using User = MainWindow::User;
	//using String = MainWindow::String;
	//using Messages = MainWindow::Messages;
	
	MessageBox(MainWindow&);
	
	void update(const std::string&, Messages&);
	void writeLeft(const std::string& msg);
	void writeRight(const std::string& msg);
	QTextEdit* getMessageText();
	QLayout* getMessageBox();

private:
	MainWindow& mainWindow_;
	QVBoxLayout* messageBox_;
	QTextEdit* messageText_;
	void createMessageBox();
//	Conversation conversation;
//	QVBoxLayout* messageTextLayout;
};

#endif
