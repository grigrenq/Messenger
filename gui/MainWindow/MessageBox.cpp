#include "MessageBox.hpp"
#include "../../core/ExtractWord.hpp"


MessageBox::MessageBox(MainWindow& mw)
	: mainWindow_(mw)
{
	createMessageBox();
//	mainWindow.rightSide->addLayout(messageBox);
}
void MessageBox::createMessageBox()
{
	messageBox_ = new QVBoxLayout();
	messageText_ = new QTextEdit();
	messageText_->setReadOnly(true);
	messageBox_->addWidget(messageText_);
//	messageTextLayout = new QVBoxLayout();
}		

void MessageBox::update(const MessageBox::String& mylogin, Messages& msgs)
{
	ExtractWord extractWord;
	for(auto msg : msgs) {
		MessageBox::String currentLogin = extractWord(msg);
		if(mylogin == currentLogin) {
			writeLeft(msg);
		}
		else {
			writeRight(msg);
		}
	}
}

void MessageBox::writeLeft(const MessageBox::String& msg)
{
	//conversation.push_back(">>>>>>>>>\n");
	//conversation.push_back(msg);
}

void MessageBox::writeRight(const MessageBox::String& msg)
{
	//conversation.push_back("<<<<<<<<<\n");
	//conversation.push_back(msg);
}

QTextEdit* MessageBox::getMessageText()
{
	    return messageText_;
}

QLayout* MessageBox::getMessageBox()
{
	    return messageBox_;
}
