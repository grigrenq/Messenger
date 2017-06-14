#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QIcon>
#include <QScrollBar>
#include <QScrollArea>

class login_window : public QWidget
{
private:
    QGridLayout *mainLayout;
    QLayout *leftSide;
    QVBoxLayout *rightSide;
    QLayout *messageBox;
    QLayout *writeBox;
    QLabel *leftLabel;
    QLabel *messageLabel;

public:
    login_window(){
        create_layout();
    };
    void create_layout();
    
};
