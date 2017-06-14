#ifndef REGISTRATIONWINDOW_HPP
#define REGISTRATIONWINDOW_HPP

#include <QMainWindow>
#include <QLayout>
#include <QString>

class QLineEdit;
class QPushButton;

#include "../core/InputValidator.hpp"
#include "../core/Controller.hpp"

class RegistrationWindow : public QMainWindow
{
	Q_OBJECT

public:
	typedef std::string String;

	RegistrationWindow(Controller&);

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
