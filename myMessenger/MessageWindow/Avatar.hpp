#include <QMainWindow>
#include <QLabel>
#include<QVBoxLayout>
#include<Qt>
#include "Client.cpp"
class Avatar:public QLabel
{
	Q_OBJECT
private:
	QLabel* avName=new QLabel(this);
	QLabel* avSurname=new QLabel(this);
	QLabel* avLogin=new QLabel(this);
	QLabel* avStatus=new QLabel(this);
	QLabel* avCount=new QLabel(this);
public:
	Avatar(user&,MainWindow&);
public slots:
	avatarCklicked();
};

