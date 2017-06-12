#HeaderServer := Server.hpp
#HeaderClient := Client.hpp
#HeaderController := Controller.hpp

run:	Main.cpp Server.o Client.o Controller.o Includes.hpp DBController.hpp ServerUser.hpp ClientUser.hpp
	g++ -std=c++11 Main.cpp Server.o Client.o Controller.o -o run -lpthread

Server.o:   Server.hpp Server.cpp Includes.hpp
	g++ -c -std=c++11 Server.cpp -o Server.o

Client.o:   Client.hpp Client.cpp Includes.hpp
	g++ -c -std=c++11 Client.cpp -o Client.o

Controller.o:	Controller.hpp Controller.cpp Includes.hpp
	g++ -c -std=c++11 Controller.cpp -o Controller.o

.PHONY:
clean:
	rm *.o run
