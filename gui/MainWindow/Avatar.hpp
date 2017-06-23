/** 
 *  @file    Avatar.hpp
 *  @author  GRI Team
 *  @date    06/23/2018  
 *  @version 1.0  
 *  @brief ....
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
*  @brief ....  
*/  
class Avatar : public QLabel
{
	Q_OBJECT

public:
	using User = MainWindow::User;
	using String = MainWindow::String;

	//Avatar(User&);
	
	/** 
        *   @brief  ....    
        *   @param  .... 
	*   @param  ....
  	*/  
	Avatar(User&, MainWindow&);
	
	/** 
        *   @brief  ....    
        *   @param  bool 
  	*   @return void
  	*/  
	void setStatus(bool);
	
	/** 
        *   @brief  ....    
        *   @param  no parametrs 
  	*   @return bool
  	*/  
	bool getStatus() const;

	/** 
        *   @brief  ....    
        *   @param  no parametrs  
  	*   @return void
  	*/  
	void incrementCount(); 
	
	/** 
        *   @brief  ....   
        *   @param  no parametrs  
  	*   @return ....
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
