#include<QApplication>
#include"mainWindow.cpp"
//It is a comment

int main(int argc,char** argv)
{
	QApplication app(argc,argv);
	mainWindow mw;
	mw.show();
	return app.exec();
}
