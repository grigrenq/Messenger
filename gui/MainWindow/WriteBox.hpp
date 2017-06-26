/** 
 *  @file    WriteBox
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0  
 *  @brief Contains WriteBox class which is inherited from QObject class.
 */


#ifndef WRITEBOX_HPP
#define WRITEBOX_HPP

#include <string>
#include <QObject>

class QLayout;
class QTextEdit;
class QPushButton;

//#include "MainWindow.hpp"
class MainWindow;


/**
*  @brief Class for creating messaging area, i.e area containing text field for writing messages and a button for sending them.
*/ 
class WriteBox: public  QObject
{
	Q_OBJECT

public:
	using String = std::string;
	//using String = MainWindow::String;


	/** 
        *   @brief  Function for creating objects of type WriteBox.
        *   @param  The only parameter is MainWindow&.
  	*/  
	WriteBox(MainWindow&);

	/** 
        *   @brief  Function for getting layout on which corresponding text field and button are located.    
        *   @param  no parametrs  
  	*   @return QLayout*.
  	*/  
	QLayout* getWriteBox();

public slots:
	void sendMessage();

private:
	void createWriteBox();
    bool isEmptyWriteBox();
	
	MainWindow& mainWindow_;
	QLayout* writeBox_;
	QTextEdit* textEdit_;
	QPushButton* sendButton_;

	static const size_t maxMessageSize = 4000;
};

#endif
