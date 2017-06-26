/** 
*  @file    RegistrationWindow.hpp
*  @author  GRI Team
*  @date    06/14/2017  
*  @version 1.0
*  @brief Contains the RegistrationWindow class which is inherited from QWidget class.
*/


#ifndef REGISTRATIONWINDOW_HPP
#define REGISTRATIONWINDOW_HPP

class QLineEdit;
class QPushButton;
class QApplication;

#include <QMainWindow>
#include <QLayout>
#include <QString>
#include <QPalette>
#include <QWidget>

#include "../core/InputValidator.hpp"
#include "../core/Controller.hpp"

/**
*  @brief Class for creating a GUI for registration window and checking if login, name, surname and password are valid.  
*/

class RegistrationWindow : public QWidget
{
	Q_OBJECT

public:
	using String = std::string;
        /** 
        *   @brief Function for creating objects of type RegistrationWindow 
        *   @param  The only parameter is Controller&.  
        */
	RegistrationWindow(Controller&);


public slots:
	void checkLogin(const QString&);
	void checkName(const QString&);
	void checkSurname(const QString&);
	void checkPassword(const QString&);
	void checkPasswords(const QString&);
	
    void sendRegistrationReq();

private:
    

        /** 
        *   @brief  addPushButton ...   
        *   @param no parametrs 
        *   @return void
        */  
	void addPushButton();
    
	
        /** 
        *   @brief  addLineEdit....   
        *   @param  no parametrs 
        *   @return void
        */
	void addLineEdit();
    
        /** 
        *   @brief  addStatusBar...   
        *   @param  no parametrs 
        *   @return void
        */
    void setBackground();
//	void addStatusBar();

        /** 
        *  @brief  addPic....   
        *   @param  no parametrs 
        *   @return void
        */
	void addPic();
    
        /** 
        *   @brief  addLayout...   
        *   @param  no parametrs 
        *   @return void
        */
    void addLayout();

        /** 
        *   @brief  addIcon...  
        *   @param  no parametrs 
        *   @return void
        */
	void addIcon();
  
        /** 
        *   @brief  connectLines....   
        *   @param  no parametrs 
        *   @return void
        */
	void connectLines();
    void setTipColor();
/*
	void addPushButton();
	void addLineEdit();
	void addStatusBar();
	void addPic();
	void addLayout();
	void addIcon();
	void connectLines();
*/	
    QVBoxLayout* mainLayout_;
	QPushButton* signUp_;
	QLineEdit* login_;
	QLineEdit* name_;
	QLineEdit* surname_;
	QLineEdit* password1_;
	QLineEdit* password2_;
    QPixmap* pix_;
	QApplication* app_;

    QPalette palette_;

	Controller& controller_;
	InputValidator validator_;
};

#endif
