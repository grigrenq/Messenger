/** 
 *  @file    WriteBox
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0  
 *  @brief ....
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
*  @brief ....  
*/ 
class WriteBox: public  QObject
{
	Q_OBJECT

public:
	using String = std::string;
	//using String = MainWindow::String;


	/** 
        *   @brief  ....    
        *   @param  ....
  	*/  
	WriteBox(MainWindow&);

	/** 
        *   @brief  ....    
        *   @param  no parametrs  
  	*   @return ....
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
};

#endif
