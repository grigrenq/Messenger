#include "../core/Client.hpp"
#include "../core/Controller.hpp"


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
	Controller controller(c);
	controller.run();

	return app.exec();
}

