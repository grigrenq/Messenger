
#include "../core/Client.hpp"
#include "../core/Controller.hpp"
#include "./MainWindow/MainWindow.hpp"

#include "./MainWindow/MainWindow.hpp"
#include <QApplication>


int main(int argc, char* argv[])
{  
	QApplication app(argc, argv);


	std::string host;
	if (argc > 1) {
		host = argv[1];
		std::cout << host << std::endl;
	}
	else {
		std::cout << "host = " << DEFAULT_HOST << std::endl;
	}

	Client c;
	MainWindow *p = nullptr;
	Controller controller(c, p);
	controller.run();
<<<<<<< HEAD
	MainWindow* p = new MainWindow(controller);
	p->show();
=======
	p = new MainWindow(controller);
>>>>>>> e0d297522b2942ba772e2f474562781937a8ce3b

	return app.exec();
}

