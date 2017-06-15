#ifndef WRITEBOX_HPP
#define WRITEBOX_HPP

#include <string>
#include <QObject>

class QLayout;
class QTextEdit;
class QPushButton;

//#include "MainWindow.hpp"
class MainWindow;
class WriteBox: public  QObject
{
	Q_OBJECT

public:
	using String = std::string;
	//using String = MainWindow::String;

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
