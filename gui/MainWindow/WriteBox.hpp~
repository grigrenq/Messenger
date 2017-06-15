#ifndef WRITEBOX_HPP
#define WRITEBOX_HPP


class QLayout;
class QTextEdit;
class QPushButton;

#include "MainWindow.hpp"

class WriteBox
{
	Q_OBJECT

public:

	WriteBox(MainWindow&);

public slots:
	void sendMessage();

private:
	void createWriteBox();
	
	MainWindow& mainWindow;
	QLayout* writeBox;
	QTextEdit* textEdit;
	QPushButton* sendButton;
};

#endif
