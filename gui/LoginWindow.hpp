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
#include <QString>
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QSpacerItem;
class QLabel;
class QPixmap;
class QPalette;
class QIcon;
class QApplication;
class QToolTip;

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
	using Stringi = std::string;

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
	void showLogWindow();	//???
    void hideLogWindow();
    void showRegWindow();
    void hideRegWindow();

public slots:
    void openRegWin();
	void checkLogin(const QString&);
	void checkPassword(const QString&);
	void sendLoginReq();
	void showLogSlot();
    void hideLogSlot();
    void showRegSlot();
    void hideRegSlot();

signals:
	void showLogSignal();
    void hideLogSignal();
    void showRegSignal();
    void hideRegSignal();

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
   
    QLineEdit* loginField;
    QLineEdit* passwordField;
    QPushButton* loginButton;
    QPushButton* regisButton;
    QVBoxLayout* vLayout;
    QLabel* loginLabel;
    QLabel* passwordLabel;
    QLabel* logo;
    QPalette* pal;
    QPixmap* pix;
    QIcon* icon;
    RegistrationWindow* regWin;
    QApplication* app;

    Controller& controller;
    InputValidator validator;
};

#endif
