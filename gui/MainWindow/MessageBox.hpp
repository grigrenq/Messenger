#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <string>
#include <list>
#include <QVBoxLayout>
#include <QTextEdit>


#include "../../core/ClientUser.hpp"

class QLayout;
class QTextEdit;

//#include "MainWindow.hpp"
class MainWindow;
class MessageBox
{
public:
	using User = ClientUser;
	using Messages = std::list<std::string>;
	//using User = MainWindow::User;
	//using String = MainWindow::String;
	//using Messages = MainWindow::Messages;
	
	MessageBox(MainWindow&);
	
	void createMessageBox();
	void update(const std::string&, Messages&);
	void writeLeft(const std::string& msg);
	void writeRight(const std::string& msg);

private:
	MainWindow& mainWindow;
	QVBoxLayout* messageBox;
	QTextEdit* messageText;
//	Conversation conversation;
//	QVBoxLayout* messageTextLayout;
};

#endif
