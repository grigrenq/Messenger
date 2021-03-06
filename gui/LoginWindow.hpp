/** 
*  @file    LoginWindow.hpp
*  @author  GRI Team
*  @date    06/14/2017  
*  @version 1.0 
*  @brief Contains LoginWindow class which is inherited from QWidget class.  
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
*  @brief Class which creates a GUI for login window and checks if login and password are valid.  
*/  
class LoginWindow : public QWidget
{
    Q_OBJECT

public:
	using String = std::string;

        /** 
        *   @brief Function for creating objects of type LoginWindow.
        *   @param The only parameter is Controller&.
        */  
        LoginWindow(Controller&);
	
        /** 
        *   @brief Function for closing registration window    
        *   @param no parameters 
        *   @return void
        */  
	void closeRegWindow();
	void showLogWindow();
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
