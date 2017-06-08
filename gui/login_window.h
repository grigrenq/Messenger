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
#include "registration.hpp"

class login_window : public QWidget
{
    Q_OBJECT

public:
    login_window();

public slots:
    void open_reg_win();

public:
    void create_layout();
    void create_buttons();
    void create_text_edit();
    void create_username_label();
    void create_password_label();
    void set_logo();
    void set_background();
    void set_window_icon();
    
private:
    QLineEdit* m_login_text;
    QLineEdit* m_password_text;
    QPushButton* m_login_button;
    QPushButton* m_regis_button;
    QVBoxLayout* m_v_layout;
    QLabel* m_username_label;
    QLabel* m_password_label;
    QLabel* m_logo;
    QPalette* m_pal;
    QPixmap* m_pix;
    QIcon* m_icon;
    MainWindow* m_reg_win;

};
