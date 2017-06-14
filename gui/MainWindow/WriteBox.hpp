class QLayout;
class QTextEdit;
class QPushButton;


#include "MainWindow.hpp"


class WriteBox
{

public:
	WriteBox(MainWindow& mw)
		: mainWindow(mw)
	{
		//
	}

private:
	void createWriteBox();

	MainWindow& mainWindow;

	QLayout* writeBox;
	QTextEdit* textEdit;
	QPushButton* sendButton;
};
