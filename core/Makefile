OFiles := Server.o ServerUser.o ClientUser.o ExtractWord.o Conversation.o TransportLayer.o
LogFiles := ./Log/*.txt
UsersFiles := ./Server/Users/*.txt ./Server/PendingMessages/*.txt ./Server/Conversations/*.txt

run:	Main.cpp $(OFiles) Includes.hpp
	g++ -std=c++11 -Wall -pedantic Main.cpp $(OFiles) -o run -lpthread

Server.o:   Server.hpp Server.cpp Includes.hpp MessageTypes.hpp TransportLayer.o DBController.hpp DBController.icpp
	g++ -c -std=c++11 -Wall -pedantic Server.cpp -o Server.o

#DBController.o:   DBController.hpp Conversation.o ExtractWord.o Files.hpp
#	g++ -c -std=c++11 -Wall -pedantic DBController.cpp -o DBController.o

ServerUser.o:	ServerUser.hpp ServerUser.cpp Includes.hpp ExtractWord.o Files.hpp
	g++ -c -std=c++11 -Wall -pedantic ServerUser.cpp -o ServerUser.o

ClientUser.o: ClientUser.hpp ClientUser.cpp Includes.hpp ExtractWord.o Files.hpp
	g++ -c -std=c++11 -Wall -pedantic ClientUser.cpp -o ClientUser.o

ExtractWord.o: ExtractWord.hpp ExtractWord.cpp
	g++ -c -std=c++11 -Wall -pedantic ExtractWord.cpp -o ExtractWord.o

Conversation.o: Conversation.hpp Conversation.cpp
	g++ -c -std=c++11 -Wall -pedantic Conversation.cpp -o Conversation.o

TransportLayer.o: TransportLayer.hpp TransportLayer.cpp
	g++ -c -std=c++11 -Wall -pedantic TransportLayer.cpp -o TransportLayer.o

.PHONY:
clean:
	rm *.o run $(LogFiles)

.PHONY:
cleanUsers:
	rm $(UsersFiles)

