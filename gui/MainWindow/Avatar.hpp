/** 
*  @file    Avatar.hpp
*  @author  GRI Team
*  @date    06/23/2017  
*  @version 1.0  
*  @brief Contains Avatar class which is inherited from QLabel class.
*/
#ifndef AVATAR_HPP
#define AVATAR_HPP

#include <Qt>
#include <QLabel>
#include <QMainWindow>
#include "../../core/ClientUser.hpp"
#include "MainWindow.hpp"

class QEvent;
class QMouseEvent;

/**
*  @brief Class for creating GUI for Avatar, that contains all registered users' logins and their statuses.
*/  
class Avatar : public QLabel
{
	Q_OBJECT

public:
	using User = MainWindow::User;
	using String = MainWindow::String;

	//Avatar(User&);
	
	/** 
        *   @brief  Function for creating objects of type Avatar. 
        *   @param  First parameter - User&  
	*   @param  Second parameter - MainWindow&
  	*/  
	Avatar(User&, MainWindow&);
	
	/** 
        *   @brief  Function for setting user's status.    
        *   @param  The only parameter is bool. 
  	*   @return void
  	*/  
	void setStatus(bool);
	
	/** 
        *   @brief  Function for getting user's status.   
        *   @param  no parametrs 
  	*   @return bool
  	*/  
	bool getStatus() const;
	
	 
	const char* getLogin(int);
        /** 
        *   @brief  Function for obtaining login of registered user.    
        *   @param  no parametrs  
  	*   @return std::string 
  	*/ 
	String getLogin();

signals:
	void clicked();

public slots:
	void openConversation();

private:
	void mousePressEvent(QMouseEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);

	User& user_;
	MainWindow& mainWindow_;
	QLabel* avName_;
	QLabel* avSurname_;
	QLabel* avLogin_;
	QLabel* avStatus_;
	QLabel* avCount_;

    bool status_;
	int unreadMessages_;
};

#endif
