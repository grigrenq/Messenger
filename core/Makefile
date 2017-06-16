OFiles := Server.o DBController.o ServerUser.o ExtractWord.o Conversation.o 


run:	Main.cpp $(OFiles) Includes.hpp
	g++ -std=c++11 Main.cpp $(OFiles) -o run -lpthread

Server.o:   Server.hpp Server.cpp Includes.hpp MessageTypes.hpp
	g++ -c -std=c++11 Server.cpp -o Server.o

DBController.o:   DBController.hpp DBController.cpp
	g++ -c -std=c++11 DBController.cpp -o DBController.o

ServerUser.o:	ServerUser.hpp ServerUser.cpp
	g++ -c -std=c++11 ServerUser.cpp -o ServerUser.o

ExtractWord.o: ExtractWord.hpp ExtractWord.cpp
	g++ -c -std=c++11 ExtractWord.cpp -o ExtractWord.o

Conversation.o: Conversation.hpp Conversation.cpp
	g++ -c -std=c++11 Conversation.cpp -o Conversation.o

.PHONY:
clean:
	rm *.o run ./ClientLog/*.txt ./ServerLog/*.txt ./Server/Users/users.txt
