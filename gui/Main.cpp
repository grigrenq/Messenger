
#include "../core/Client.hpp"
#include "../core/Controller.hpp"

#include "./MainWindow/MainWindow.hpp"
#include <QApplication>


int main(int argc, char* argv[])
{  
	QApplication app(argc, argv);

	Client c;
	Controller controller(c);
	std::string login;
	if (argc > 1) {
		login = argv[1];
	}
	controller.run();

	return app.exec();
}

