/** 
*  @file    Avatar.hpp
*  @author  GRI Team
*  @date    06/23/2017  
*  @version 1.0  
*  @brief creating GUI where show all users who registred in GRI and there status
*/
#ifndef AVATAR_HPP
#define AVATAR_HPP

#include <Qt>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <MainWindow.hpp>
#include <QMouseEvent>
#include "../../core/ClientUser.hpp"

class MainWindow;
class QEvent;



/**
*  @brief Avatar creating GUI where show all users who registred in GRI and there status
*/  
class Avatar : public QLabel
{
	Q_OBJECT

public:
	using User = MainWindow::User;
	using String = MainWindow::String;

	//Avatar(User&);
	
	/** 
        *   @brief  Avatar constructor for class Avatar,thats created all avatar's labels and added style 
        *   @param  reference of User  
	*   @param  reference of MainWindow
  	*/  
	Avatar(User&, MainWindow&);
	
	/** 
        *   @brief  setStatus about status users if user online or ofline    
        *   @param  bool 
  	*   @return void
  	*/  
	void setStatus(bool);
	
	/** 
        *   @brief  getStatus show status users   
        *   @param  no parametrs 
  	*   @return bool
  	*/  
	bool getStatus() const;
	
	/** 
        *   @brief  getLogin  returned  parametrs user who log in this moment    
        *   @param  no parametrs  
  	*   @return const char*
  	*/  
	const char* getLogin();

signals:
	void clicked();

public slots:
	void openConversation();

private:
	User& user_;
	MainWindow& mainWindow_;
	QLabel* avName_;
	QLabel* avSurname_;
	QLabel* avLogin_;
	QLabel* avStatus_;
	QLabel* avCount_;
    bool status_;
	int unreadMessages_;
	void mousePressEvent(QMouseEvent*);
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
};

#endif
