#include <QTextEdit>
#include <QLayout>
#include <QVBoxLayout>

#include "MessageBox.hpp"
#include "../../core/WordExtractor.hpp"


MessageBox::MessageBox(MainWindow& mw)
	: mainWindow_(mw)
{
	createMessageBox();
	//mainWindow_.rightSide_->addLayout(messageBox_);	//??????????
}
void MessageBox::createMessageBox()
{
	messageBox_ = new QVBoxLayout();
	messageText_ = new QTextEdit();
	messageText_->setReadOnly(true);
	messageBox_->addWidget(messageText_);
//	messageTextLayout = new QVBoxLayout();
}		

void MessageBox::update(const String& mylogin, Messages& msgs)
{
	WordExtractor we;
    delete messageText_;
    messageText_ = nullptr;
    messageText_ = new QTextEdit();
	messageText_->setReadOnly(true);
	messageBox_->addWidget(messageText_);
    for(auto msg : msgs) { 
        String currentLogin = we(msg);
        if(mylogin == currentLogin) {
           messageText_->setText( messageText_->toPlainText() + ">>>>>>>>>\n" + (QString::fromStdString(msg)) + "\n");
        }
        else if(msg != "") {
            messageText_->setText(  messageText_->toPlainText() + "<<<<<<<<\n" +  (QString::fromStdString(msg)) + "\n");
        }
    }
}

void MessageBox::writeLeft(const MessageBox::String& )
{
//    std::cout << __FUNCTION__ <<std::endl;
//	messageText_->setPlainText(">>>>>>>>>\n");
//	messageText_->setPlainText(QString::fromStdString(msg));
}

void MessageBox::writeRight(const MessageBox::String&)
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
