#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP


#include "MainWindow.hpp"

class MessageBox
{
	public:
		MessageBox(MainWindow& mw)
			: mainWindow(mw) 
		{
		}

	

		void createMessageBox()
		{
			messageBox = new QVBoxLayout();
			rightSide->addLayout(messageBox);
			messageText=new QTextEdit(this);
			messageText->setReadOnly(true);
			messageBox->addWidget(messageText);
			messageTextLayout = new QVBoxLayout();
		}		

	private:
		MainWindow& mainWindow;
		QVBoxLayout* messageBox;
		QTextEdit* messageText;
		QVBoxLayout* messageTextLayout;
};

#endif
