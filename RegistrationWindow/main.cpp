#include <QApplication>
#include "registration.cpp"

int main(int argc,char** argv)
{
	QApplication app(argc,argv);
	RegistrationWindow rw;
	rw.show();
	return app.exec();
}
