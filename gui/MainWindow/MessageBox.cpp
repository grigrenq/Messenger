#include "MessageBox.hpp"
#include "../../core/ExtractWord.hpp"

//#include "MainWindow.hpp"

MessageBox::MessageBox(MainWindow& mw)
	: mainWindow(mw)
{
	createMessageBox();
	//mainWindow->rightSide->addLayout(messageBox);
}
void MessageBox::createMessageBox()
{
	messageBox = new QVBoxLayout();
	messageText = new QTextEdit(this);
	messageText->setReadOnly(true);
	messageBox->addWidget(messageText);
//	messageTextLayout = new QVBoxLayout();
}		

void MessageBox::update(const std::string& mylogin, const Messages& msgs)
{
	std::string msg;
	for(msg : msgs) {
		std::string currentLogin = extractWord(msg);
		if(mylogin == currentLogin) {
			writeLeft(msg);
		}
		else {
			writeRight(msg);
		}
	}
}

void MessageBox::writeLeft(const std::string& msg)
{
	//conversation.push_back(">>>>>>>>>\n");
	//conversation.push_back(msg);
}

void MessageBox::writeRight(const std::string& msg)
{
	//conversation.push_back("<<<<<<<<<\n");
	//conversation.push_back(msg);
}

