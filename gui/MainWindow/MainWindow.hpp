/** 
 *  @file    MainWindow.hpp
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0  
 *  @brief Contains MainWindow class which is inherited from QWidget class.
 */

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPixmap>
#include <QPalette>
#include <QScrollBar>
#include <list>
#include <string>
#include <memory>

#include "../../core/Controller.hpp"

class QTextEdit;
class QScrollArea;
class QLabel;
class QVBoxLayout;
class QGridLayout;
class QIcon;
class QCloseEvent;
class Avatar;
class Controller;
class MessageBox;
class WriteBox;


/**
*  @brief Class for creating MainWindow, i.e window that contains list of
*  avatars, writing box and message box.  
*/ 
class MainWindow : public QWidget
{
	Q_OBJECT

public:
	using String = Controller::String;
	using User = Controller::User;
	using UserPtr = User*;
	using Users = Controller::Users;
	using Messages = Controller::User::Messages;
	using AvatarPtr = std::shared_ptr<Avatar>;
	using Avatars = std::list<AvatarPtr>;
	using AvatarsIter = Avatars::iterator;

	
	/** 
        *   @brief  Function for creating objects of type MainWindow.    
        *   @param  The only parameter is Controller&. 
  	*/  
	MainWindow(Controller&);

	/** 
        *   @brief  Function for updating MainWindow after such cases as
        *   registration of a new user, logging out of a user...e.t.c.    
        *   @param  The only paramter is User& u. 
  	*   @return void
  	*/  
	void updateMainWindow(User& u);

	/** 
        *   @brief  Function for updating MainWindow after such cases as registration of a new user, logging out of a user...e.t.c.     
        *   @param  The only parameter is Users& users.
  	*   @return void
  	*/  
	void updateMainWindow(Users& users);
	
    void clearMessages(User& u)
    {
        controller_.clearMessages(u);
    }
        /** 
        *   @brief  Function for setting address to user.    
        *   @param  The only parameter is User& u. 
  	*   @return void
  	*/  
	void setUser(User& u);	

	/** 
        *   @brief  Function for updating MessageBox.    
        *   @param  no parametrs  
  	*   @return void
  	*/  
	void updateMessageBox();

	/** 
        *   @brief  Function for sending message to a user.    
        *   @param  The only parameter is std::string& msg. 
  	*   @return void
  	*/  
	void sendMessage(String& msg);

	/** 
        *   @brief  Function for sending conversation request to server.    
        *   @param  The only parameter is const std::string&. 
  	*   @return void
  	*/  
	void sendConvRequest(const String&);

	/** 
        *   @brief  Function for showing the MainWindow.    
        *   @param  no parametrs  
  	*   @return void
  	*/  
	void showWindow();
	void hideWindow();

	void closeEvent(QCloseEvent*) override;

public slots:
	void showSlot();
	void hideSlot();
	void updateSlot(User);
	void updateSlot(Users);

signals:
	void showSignal();
	void hideSignal();
	void updateSignal(User);
	void updateSignal(Users);

private:
    void createLayout();
	void createLayouts();
	void addAvatar(Avatar*);
	void addAvatars();
	void setWindowIcon();

	void updateMainWindowHelper(User&);
	void updateMainWindowHelper(Users&);
	AvatarsIter find(const User& u);

	QGridLayout* mainLayout_;
    QLayout* leftSide_;
    QVBoxLayout* rightSide_;
	QLayout* avLay_;
    QLabel* leftLabel_;
    QLabel* messageLabel_;
	QScrollArea* scrollArea_;
	QWidget* scrollWidget_;
	QTextEdit* messageText_;
	QLayout* messageTextLayout_;
	QIcon* windowIcon_;

	Avatars avatars_;
	Controller& controller_;
	UserPtr userPtr_;
	MessageBox* messageBox_;
	WriteBox* writeBox_;
};


#endif
