#include <QMainWindow>
#include <QLayout>

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QVBoxLayout* mainLayout;			

public:
	MainWindow();
	void addPushButton();
	void addLineEdit();
	void addStatusBar();
	void addPic();
	void addLayout();
	void addIcon();

public slots:
	void sendDetails();
};
