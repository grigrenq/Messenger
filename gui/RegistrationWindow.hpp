/** 
*  @file    RegistrationWindow.hpp
*  @author  GRI Team
*  @date    06/14/2017  
*  @version 1.0
*  @brief RegistrationWindow.hpp creating a GUI for registration window and connection   for checking params for registration
*/


#ifndef REGISTRATIONWINDOW_HPP
#define REGISTRATIONWINDOW_HPP

class QLineEdit;
class QPushButton;

#include <QMainWindow>
#include <QLayout>
#include <QString>

#include "../core/InputValidator.hpp"
#include "../core/Controller.hpp"

/**
*  @brief RegistrationWindow class which creates the GUI for login window.  
*/

class RegistrationWindow : public QMainWindow
{
	Q_OBJECT

public:
	using String = std::string;

        /** 
        *   @brief RegistrationWindow constructor for class RegistrationWindow which     creates GUI for registration window 
        *   @param  is an initialized......???  
        */
	RegistrationWindow(Controller&);

        /** 
        *   @brief  addPushButton ...   
        *   @param no parametrs 
        *   @return void
        */  
//	void addPushButton();
    
        /** 
        *   @brief  addLineEdit....   
        *   @param  no parametrs 
        *   @return void
        */
//	void addLineEdit();

        /** 
        *   @brief  addStatusBar...   
        *   @param  no parametrs 
        *   @return void
        */
//	void addStatusBar();

        /** 
        *  @brief  addPic....   
        *   @param  no parametrs 
        *   @return void
        */
//	void addPic();
    
        /** 
        *   @brief  addLayout...   
        *   @param  no parametrs 
        *   @return void
        */
//	void addLayout();

        /** 
        *   @brief  addIcon...  
        *   @param  no parametrs 
        *   @return void
        */
//	void addIcon();
  
        /** 
        *   @brief  connectLines....   
        *   @param  no parametrs 
        *   @return void
        */
//	void connectLines();

public slots:
	void checkLogin(const QString&);
	void checkName(const QString&);
	void checkSurname(const QString&);
	void checkPassword(const QString&);
	void checkPasswords(const QString&);

	void sendRegistrationReq();

private:
    

	void addPushButton();
	void addLineEdit();
	void addStatusBar();
	void addPic();
	void addLayout();
	void addIcon();
	void connectLines();

	QVBoxLayout* m_mainLayout;
	QPushButton* signUp;
	QLineEdit* login;
	QLineEdit* name;
	QLineEdit* surname;
	QLineEdit* password1;
	QLineEdit* password2;

	Controller& controller;
	InputValidator validator;
};

#endif
