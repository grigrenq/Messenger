
#include "../core/Server.hpp"
#include "../core/Client.hpp"
#include "../core/Controller.hpp"


#include <QApplication>


void* startControllerOperating(void*)
{
	Client c;
	Controller controller(c);
	controller.run();
	return nullptr;
}


int main(int argc, char* argv[])
{  
	QApplication app(argc, argv);


    if (argc > 1) {
		std::string str(argv[1]);
		std::cout << str << std::endl;
        if (str == "Server"){
            Server s;
            s.run();
        }
        else if (str == "Client") {
			std::cout << "host = " << DEFAULT_HOST << std::endl;
			std::shared_ptr<pthread_t> th(new pthread_t);
			if (pthread_create(&(*th), NULL, startControllerOperating, NULL)) {
				std::cout << "An error occurred during thread creation process.";
				return 1;
			}
        }
        else {
            std::cout << "Neither\n";
		}
    }
    else {
        std::cout << "Run with  Server or Client as parameter: ./run Server or ./run Client\n";
	}
	return app.exec();
}

