#include "login_window.h"
#include <iostream>
#include<QLabel>
login_window::login_window()
{
    this->setGeometry(50,50,850,600);
    this->setMinimumHeight(300);
    this->setMinimumWidth(350);
    this->setMaximumHeight(1700);
    this->setMaximumWidth(1700);

    set_background();
    set_logo();
    create_text_edit();
    create_buttons();
    create_username_label();
    create_password_label();
    create_layout();
    this->setLayout(m_v_layout);
    set_window_icon();
}

void login_window::create_layout()
{
    m_v_layout = new QVBoxLayout();
    //m_v_layout->setContentsMargins(15, 5, 1300, 0);
    m_v_layout->addSpacing(12);
    m_v_layout->addWidget(m_username_label);
    m_v_layout->addWidget(m_login_text);
    m_v_layout->addWidget(m_password_label);
    m_v_layout->addWidget(m_password_text);
    m_v_layout->addWidget(m_login_button);
    m_v_layout->addWidget(m_regis_button);
    m_v_layout->addSpacerItem(new QSpacerItem(400, 400, 
                           QSizePolicy::Preferred, QSizePolicy::Expanding));
       
 //   m_v_layout->setMinimumSize(80);
//   m_v_layout->setMaximumSize(80);
    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    label1->setGeometry(15,5,200,50);
    label2->setGeometry(15,65,200,50);
    
    label1->setMinimumSize(80,100);
    label1->setMaximumSize(8,100);
    label2->setMinimumSize(80,100);
    label2->setMaximumSize(80,100);
}

void login_window::create_buttons()
{
    m_login_button = new QPushButton("LOG IN", this);
    m_login_button->setStyleSheet("QPushButton{background-color: #456ba8;color:white;}");
    m_login_button->setMinimumSize(80, 20);
    m_login_button->setMaximumSize(40, 40);
    m_regis_button = new QPushButton("CREATE NEW ACCOUNT", this);
    m_regis_button->setStyleSheet("QPushButton{background-color: #456ba8; color:white;}");
    m_regis_button->setMinimumSize(200, 20);
    m_regis_button->setMaximumSize(40, 40);
    QObject::connect(m_regis_button, SIGNAL(clicked()), 
                        this, SLOT(open_reg_win()));
}

void login_window::create_text_edit()
{
    m_login_text = new QLineEdit(this);
    m_password_text = new QLineEdit(this);
    m_password_text->setEchoMode(QLineEdit::Password);
    m_login_text->setMinimumHeight(30);
    m_login_text->setMinimumWidth(300);
    m_login_text->setMaximumHeight(30);
    m_login_text->setMaximumWidth(300);
    m_password_text->setMinimumHeight(30);
    m_password_text->setMinimumWidth(300);
    m_password_text->setMaximumHeight(30);
    m_password_text->setMaximumWidth(300);

}

void login_window::create_username_label()
{
    m_username_label = new QLabel("Username", this);
}

void login_window::create_password_label()
{
    m_password_label = new QLabel("Password", this);
}

void login_window::set_logo()
{
    m_logo = new QLabel(this);
    m_logo->setGeometry(350, 10, 450, 450);
    QPixmap* p = new QPixmap("../back_image/asd");
    m_logo->setPixmap(*p);

}

void login_window::set_background()
{
    //m_pal = new QPalette();
    m_pix = new QPixmap("../back_image/b.jpeg");
    //*m_pix = m_pix->scaled(this->size(), Qt::IgnoreAspectRatio);
    QLabel *label1=new QLabel(this);
    label1->setGeometry(0,0,1700,1300);
    label1->setScaledContents(true);
    //m_pal->setBrush(QPalette::Background, *m_pix);
    label1->setPixmap(*m_pix);
    label1->setScaledContents(true);
    //this->setPalette(*m_pal);
}

void login_window::set_window_icon()
{
    m_icon = new QIcon("../back_image/a.png");
    this->setWindowIcon(*m_icon);
}

void login_window::open_reg_win()
{
    m_reg_win = new MainWindow;
    m_reg_win->show();
}






