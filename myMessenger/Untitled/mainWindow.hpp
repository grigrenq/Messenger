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
#include <list>
#include "Avatar.hpp"

class mainWindow : public QWidget
{
	Q_OBJECT
private:
    QGridLayout *mainLayout;
    QLayout *leftSide;
    QVBoxLayout *rightSide;
    QLayout *messageBox;
    QLayout *writeBox;
	QLayout* avLay;
    QLabel *leftLabel;
    QLabel *messageLabel;
	QScrollArea *scrollArea;
	QTextEdit* messageText;
	QLayout* messageTextLayout;

	QTextEdit *textEdit;
	QPushButton *sendButton;
	std::vector<QString> messages;
	std::list<Avatar*> avatars;
	void createLayouts();
	void createAvatar();
	void addAvatars();
	void createMessageBox();
	void createWriteBox();
public:
    mainWindow();
    void createLayout();
public slots:
	void sendMessage();
};
