#include <QTextEdit>
#include <QLayout>
#include <QVBoxLayout>

#include "MessageBox.hpp"
#include "../../core/WordExtractor.hpp"


MessageBox::MessageBox(MainWindow& mw)
: mainWindow_(mw)
{
	createMessageBox();
}

void MessageBox::createMessageBox()
{
	messageBox_ = new QVBoxLayout();
	messageText_ = new QTextEdit();
	messageText_->setReadOnly(true);
	messageBox_->addWidget(messageText_);
}		

void MessageBox::update(const String& mylogin, Messages& msgs)
{
	WordExtractor we;
    delete messageText_;
    messageText_ = nullptr;
    messageText_ = new QTextEdit();
	messageText_->setReadOnly(true);
	messageBox_->addWidget(messageText_);
	messageText_->verticalScrollBar()->setValue(messageText_->verticalScrollBar()->maximum());
    for(auto msg : msgs) { 
        String currentLogin = we(msg);
        if(mylogin == currentLogin) {
           messageText_->textCursor().insertText("\n>>>>>>>>>\n" + QString::fromStdString(msg) + "\n");
        } else {
           messageText_->textCursor().insertText("\n<<<<<<<<\n" + QString::fromStdString(msg) + "\n");
        }
    }
	messageText_->verticalScrollBar()->setValue(messageText_->verticalScrollBar()->maximum());
}


QTextEdit* MessageBox::getMessageText()
{
	    return messageText_;
}

QLayout* MessageBox::getMessageBox()
{
	    return messageBox_;
}
