#include <QLayout>
#include <QPushButton>
#include <QTextEdit>


class WriteBox:public QLayout
{
private:	
	QPushButton* send;
	QTextEdit* messageToSend;
public:
	WriteBox();
};

