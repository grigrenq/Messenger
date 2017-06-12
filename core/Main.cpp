
#include "Server.hpp"
#include "Client.hpp"
#include "Controller.hpp"


int main(int argc, char* argv[])
{  
    if (argc > 1)
    {
		std::string str(argv[1]);
		std::cout << str << std::endl;
        if (str == "Server"){
            Server s;
            s.run();
        }
        else if (str == "Client"){
			std::cout << "host = " << DEFAULT_HOST << std::endl;
            Client c;
			Controller controller(c);
            controller.run();
        }
        else
            std::cout << "Neither\n";
    }
    else
        std::cout << "Run with  Server or Client as parameter: ./run Server or ./run Client\n";
    return 0;
}
