#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <mutex>
#include <fstream>
#include <string>

#include "ServerUser.hpp"
#include "ClientUser.hpp"


class DBController
{
public:
	using ServerUsers = std::multiset<ServerUser>;
	using ClientUsers = std::list<ClientUser>;
	using String = std::string;
	using mutGuard = std::lock_guard<std::mutex>;

	DBController()
		: serverUsers(nullptr), clientUsers(nullptr) {}
	DBController(ServerUsers *su)
		: serverUsers(su), clientUsers(nullptr) {}
	DBController(ClientUsers *cu)
		: serverUsers(nullptr), clientUsers(cu) {}

	void logServer(const String& str)
	{
		mutGuard mg(mutex);
		std::ofstream ofile("./ServerLog/log.txt", std::fstream::binary | std::fstream::out | std::fstream::app);
		ofile.write(str.c_str(), str.size());
		ofile.write("\n", 1);
		ofile.close();
	}
	void logClient(const String& str)
	{
		mutGuard mg(mutex);
		std::ofstream ofile("./ClientLog/log.txt", std::fstream::binary | std::fstream::out | std::fstream::app);
		ofile.write(str.c_str(), str.size());
		ofile.write("\n", 1);
		ofile.close();
	}


	void logUsers()
	{
		mutGuard mg(mutex);
		String ps = ".............All clients are........\n...Number of clients: ";

		if (clientUsers != nullptr)	{
			std::ofstream ofile("./ClientLog/users.txt", std::fstream::binary | std::fstream::out | std::fstream::app);
			ps += std::to_string(clientUsers->size()) + "........\n";
			ofile.write(ps.c_str(), ps.size());
			String s;
			for (auto it = clientUsers->begin(); it != clientUsers->end(); ++it) {
				ClientUser* p = it->getPointer();
				s = p->toString() + '\n';
				ofile.write(s.c_str(), s.size());
			}
			ps = "..............end of the list............\n\n";
			ofile.write(ps.c_str(), ps.size());
			ofile.close();
		}
		if (serverUsers != nullptr) {
			std::ofstream ofile("./ServerLog/users.txt", std::fstream::binary | std::fstream::out | std::fstream::app);
			ps += std::to_string(serverUsers->size()) + ".........\n";
			ofile.write(ps.c_str(), ps.size());
			String s;
			for (auto it = serverUsers->begin(); it != serverUsers->end(); ++it) {
				ServerUser* p = it->getPointer();
				s = p->toStringLog() + '\n';
				ofile.write(s.c_str(), s.size());
			}
			ps = "..............end of the list............\n\n";
			ofile.write(ps.c_str(), ps.size());
			ofile.close();
		}
	}
private:
	ServerUsers *serverUsers;
	ClientUsers *clientUsers;
	std::mutex mutex;
};

#endif 
