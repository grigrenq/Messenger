#include <QMainWindow>
#include <QLayout>

class RegistrationWindow : public QMainWindow
{
Q_OBJECT

private:
	QVBoxLayout* m_mainLayout;			

public:
	RegistrationWindow();
	void addPushButton();
	void addLineEdit();
	void addStatusBar();
	void addPic();
	void addLayout();
	void addIcon();

public slots:
	void sendDetails();
};
