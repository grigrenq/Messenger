/** 
 *  @file    MessageBox.hpp
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0  
 *  @brief Contains MessageBox class.
 */

#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <string>
#include <list>

#include "MainWindow.hpp"

class QTextEdit;
class QLayout;
class QVBoxLayout;

/**
*  @brief Class for creating area where all sent messages to concrete user and received ones from him will be shown.  
*/ 
class MessageBox
{
public:
	using User = MainWindow::User;
	using String = MainWindow::String;
	using Messages = MainWindow::Messages;
	
	/** 
        *   @brief  Function for creating objects of type MessageBox.    
        *   @param  The only parameter is MainWindow&. 
  	*/  
	MessageBox(MainWindow&);

	/** 
        *   @brief  Function for updating MessageWindow for every user.    
        *   @param  First parameter - const std::string&.
	*   @param  Second parameter - Messages&.
  	*   @return void
  	*/  
	void update(const std::string&, Messages&);

	/** 
        *   @brief  Function for getting QTextEdit containing sent or recieved message. 
        *   @param  no parametrs  
  	*   @return QTextEdit*
  	*/  
	QTextEdit* getMessageText();

	/** 
        *   @brief  Function for getting layout containing MessageBox.    
        *   @param  no parametrs  
  	*   @return QLayout*.
  	*/  
	QLayout* getMessageBox();

private:
	void createMessageBox();

	MainWindow& mainWindow_;
	QVBoxLayout* messageBox_;
	QTextEdit* messageText_;
	QVBoxLayout* messageTextLayout;
};

#endif
