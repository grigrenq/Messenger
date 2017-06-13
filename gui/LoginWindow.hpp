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

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
	typedef std::string String;

    LoginWindow(Controller&);

public slots:
    void openRegWin();
	void checkLogin(const QString&);
	void checkPassword(const QString&);
	void sendLoginReq();

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
    
private:
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
