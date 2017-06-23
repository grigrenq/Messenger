/** 
 *  @file    MessageBox.hpp
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0  
 *  @brief ....
 */

#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <string>
#include <list>
#include <QVBoxLayout>
#include <QTextEdit>
#include "../../core/ClientUser.hpp"

class QLayout;
class QTextEdit;

class MainWindow;



/**
*  @brief ....  
*/ 
class MessageBox
{
public:
	using User = ClientUser;
	using Messages = std::list<std::string>;
	using String = ClientUser::String;
	//using User = MainWindow::User;
	//using String = MainWindow::String;
	//using Messages = MainWindow::Messages;
	
	/** 
        *   @brief  ....    
        *   @param  .... 
  	*/  
	MessageBox(MainWindow&);
	

	/** 
        *   @brief  ....    
        *   @param  ....
	*   @param  .... 
  	*   @return void
  	*/  
	void update(const std::string&, Messages&);

	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void writeLeft(const std::string& msg);

	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void writeRight(const std::string& msg);

	/** 
        *   @brief  ....    
        *   @param  no parametrs  
  	*   @return ....
  	*/  
	QTextEdit* getMessageText();

	/** 
        *   @brief  ....    
        *   @param  no parametrs  
  	*   @return ....
  	*/  
	QLayout* getMessageBox();

private:
	MainWindow& mainWindow_;
	QVBoxLayout* messageBox_;
	QTextEdit* messageText_;
	void createMessageBox();
//	Conversation conversation;
//	QVBoxLayout* messageTextLayout;
};

#endif
