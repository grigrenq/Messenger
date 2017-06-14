/** 
*  @file    RefistrationWindow.hpp
*  @author  GRI Team
*  @date    06/14/2017  
*  @version 1.0 
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
*  @brief RegistrationWindow class w creates the GUI for login window.  
*/

class RegistrationWindow : public QMainWindow
{
	Q_OBJECT

public:
	typedef std::string String;

        /** 
        *   @brief RegistrationWindow constructor for class RegistrationWindow 
        *   @param  is an initialized  
        */
	RegistrationWindow(Controller&);

        /** 
        *   @brief  addPushButton the values of two integer parameters.   
        *   @param  a is an initialized integer variable 
        *   @param  b is an initialized integer variable 
        *   @return void
        */  
	void addPushButton();
	void addLineEdit();
	void addStatusBar();
	void addPic();
	void addLayout();
	void addIcon();
	void connectLines();

public slots:
	void checkLogin(const QString&);
	void checkName(const QString&);
	void checkSurname(const QString&);
	void checkPassword(const QString&);
	void checkPasswords(const QString&);

	void sendRegistrationReq();

private:
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
