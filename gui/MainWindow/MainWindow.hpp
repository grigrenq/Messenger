/** 
 *  @file    MainWindow.hpp
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0  
 *  @brief ....
 */



#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
//#include <QIcon>
#include <QScrollBar>
#include <QScrollArea>
#include <list>
#include <string>
#include <memory>

#include "../../core/Controller.hpp"

class QIcon;
class Avatar;
class Controller;
class MessageBox;
class WriteBox;


/**
*  @brief ....  
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
        *   @brief  ....    
        *   @param  .... 
  	*/  
	MainWindow(Controller&);

	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void updateMainWindow(User& u);

	/** 
        *   @brief  ....  
        *   @param  ....
	*   @param  .... 
  	*   @return void
  	*/  
	void updateMainWindow(Users& users);
	
	
	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void setUser(User& u);	

	/** 
        *   @brief  .....    
        *   @param  no parametrs  
  	*   @return void
  	*/  
	void updateMessageBox();

	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void sendMessage(String& msg);

	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void sendConvRequest(const String&);

	/** 
        *   @brief  ....    
        *   @param  no parametrs  
  	*   @return void
  	*/  
	void showWindow();	//???


public slots:
	void showSlot();
	void updateSlot(User);
	void updateSlot(Users);

signals:
	void showSignal();
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
