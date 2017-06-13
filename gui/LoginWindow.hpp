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
#include "RegistrationWindow.hpp"

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow();

public slots:
    void openRegWin();

public:
    void createLayout();
    void createButtons();
    void createTextEdit();
    void createUsernameLabel();
    void createPasswordLabel();
    void setLogo();
    void setBackground();
    void setWindowIcon();
    
private:
    QLineEdit* m_loginText;
    QLineEdit* m_passwordText;
    QPushButton* m_loginButton;
    QPushButton* m_regisButton;
    QVBoxLayout* m_vLayout;
    QLabel* m_usernameLabel;
    QLabel* m_passwordLabel;
    QLabel* m_logo;
    QPalette* m_pal;
    QPixmap* m_pix;
    QIcon* m_icon;
    RegistrationWindow* m_regWin;

};
