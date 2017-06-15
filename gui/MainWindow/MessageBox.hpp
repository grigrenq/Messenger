#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <string>
#include <list>

#include "MainWindow.hpp"

class QLayout;
class QTextEdit;

class MessageBox
{
public:
	using String = std::string;
	using Messages = std::list<String>;
	
	MessageBox(MainWindow&);
	
	void createMessageBox();
	void updateMessageBox(const String&, Messages&);
	void writeLeft(String msg);
	void writeRight(String msg);

private:
	MainWindow& mainWindow;
	QVBoxLayout* messageBox;
	QTextEdit* messageText;
//	Conversation conversation;
//	QVBoxLayout* messageTextLayout;
};

#endif
