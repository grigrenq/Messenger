OFiles := Server.o DBController.o ServerUser.o ExtractWord.o Conversation.o 
LogFiles := ./ClientLog/*.txt ./ServerLog/*.txt
UsersFiles := ./Server/Users/users.txt ./Server/PendingMessages/*.txt ./Server/Conversations/*.txt

run:	Main.cpp $(OFiles) Includes.hpp
	g++ -std=c++11 -Wall -pedantic Main.cpp $(OFiles) -o run -lpthread

Server.o:   Server.hpp Server.cpp Includes.hpp MessageTypes.hpp
	g++ -c -std=c++11 -Wall -pedantic Server.cpp -o Server.o

DBController.o:   DBController.hpp DBController.cpp Files.hpp
	g++ -c -std=c++11 -Wall -pedantic DBController.cpp -o DBController.o

ServerUser.o:	ServerUser.hpp ServerUser.cpp Files.hpp
	g++ -c -std=c++11 -Wall -pedantic ServerUser.cpp -o ServerUser.o

ExtractWord.o: ExtractWord.hpp ExtractWord.cpp
	g++ -c -std=c++11 -Wall -pedantic ExtractWord.cpp -o ExtractWord.o

Conversation.o: Conversation.hpp Conversation.cpp
	g++ -c -std=c++11 -Wall -pedantic Conversation.cpp -o Conversation.o

.PHONY:
clean:
	rm *.o run $(LogFiles)

.PHONY:
cleanUsers:
	rm $(UsersFiles)
