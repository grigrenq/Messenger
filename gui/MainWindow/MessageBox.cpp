#include "MessageBox.hpp"
#include "MainWindow.hpp"

#include "../../core/ExtractWord.hpp"

MessageBox::MessageBox(MainWindow& mw)
	: mainWindow(mw)
{
	createMessageBox();
	mainWindow.rightSide->addLayout(messageBox);
}
void MessageBox::createMessageBox()
{
	messageBox = new QVBoxLayout();
	messageText = new QTextEdit(this);
	messageText->setReadOnly(true);
	messageBox->addWidget(messageText);
//	messageTextLayout = new QVBoxLayout();
}		

void MessageBox::updateMessageBox(const String& mylogin, Messages& msgs)
{
	String msg;
	for(msg in msgs) {
		String currentLogin = extractWord(msg);
		if(mylogin == currentLogin) 
			writeLeft(msg);
		else
			writeRight(msg);
	}
}

void MessageBox::writeLeft(String msg)
{
	//conversation.push_back(">>>>>>>>>\n");
	//conversation.push_back(msg);
}

void MessageBox::writeRight(String msg)
{
	//conversation.push_back("<<<<<<<<<\n");
	//conversation.push_back(msg);
}

