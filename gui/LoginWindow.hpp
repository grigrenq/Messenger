/** 
*  @file    LoginWindow.hpp
*  @author  GRI Team
*  @date    06/14/2017  
*  @version 1.0 
*  @brief LoginWindow.hpp creating a GUI for login window and connection for checking the login password 
*/


#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP


#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QIcon>
#include <QString>

#include "RegistrationWindow.hpp"
#include "../core/InputValidator.hpp"
#include "../core/Controller.hpp"

/**
*  @brief LoginWindow class which creates the GUI for login window.  
*/  
class LoginWindow : public QWidget
{
    Q_OBJECT

public:
	typedef std::string String;

        /** 
        *   @brief LoginWindow constructor for class LoginWindow which creates GUI for login window
        *   @param  is an initialized....  ??
        */  
        LoginWindow(Controller&);
	
        /** 
        *   @brief closeRegWindow closing registration window    
        *   @param no parametrs 
        *   @return void
        */  
	void closeRegWindow();



	void showWindow();	//???

public slots:
    void openRegWin();
	void checkLogin(const QString&);
	void checkPassword(const QString&);
	void sendLoginReq();
	void showSlot();

signals:
	void showSignal();

private:
    void createLayout();
    void createButtons();
    void createTextEdit();
    void createUsernameLabel();
    void createPasswordLabel();
    void setLogo();
    void setBackground();
    void setWindowIcon();
    void connectLines();
   
    QLineEdit* m_login;
    QLineEdit* m_password;
    QPushButton* m_loginButton;
    QPushButton* m_regisButton;
    QVBoxLayout* m_vLayout;
    QLabel* m_loginLabel;
    QLabel* m_passwordLabel;
    QLabel* m_logo;
    QPalette* m_pal;
    QPixmap* m_pix;
    QIcon* m_icon;
    RegistrationWindow* m_regWin;

    Controller& controller;
    InputValidator validator;
};

#endif
