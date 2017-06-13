#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Client.hpp"
#include "ClientUser.hpp"
#include "DBController.hpp"

class LoginWindow;
class RegistrationWindow;
class MessageWindow;



void* readMessage(void *);

class Controller
{
public:
	using User = ClientUser;
	using Users = std::list<User>;
	using UserIter = Users::iterator;
	using String = std::string;

	class InputReader {
		public:
			InputReader(Controller &c)
				: controller(c), stopReading(false) {}
			~InputReader() {
				stopRead();
				controller.closeConnection();
				//exit(1);
			}
			void startRead() {
				if (pthread_create(&pth, NULL, ::readMessage, this)) {
					std::cout << "Error creating thread.\n";
					return;
				}
			}
			void stopRead() {
				stopReading = true;
				pthread_join(pth, NULL);
			}
			void* readMessage() {
				String message;
				while (!stopReading) {
					std::cin.clear();
					std::getline(std::cin, message);
					if (message == "QUIT") {
						stopReading = true;
						//break;
						//exit(1);
					} else {
						controller.f(message);
					}
				}
			}
			bool stopRequested() const {
				return stopReading;
			}
			private:
				Controller &controller;
				pthread_t pth;
				bool stopReading;
		};//InputReader

	
		Controller(Client& c_);
		void run();

		String sendLoginRequest(const String& login, const String& password);
		String sendLogoutRequest();
		String sendRegistrationRequest(const String& login, const String& name,
				const String& surname, const String& password1, const String& password2);
		String sendMessageToUser(const String& toUser, String& msg);

		void f(String& str)	//for testing
		{
			String n = "name";
			String sn = "surname";
			String p = "pass";

			String type = extractWord(str, ' ');
			String login;

			if (type == "log") {
				login = extractWord(str);
				UserName = login;
				std::cout << sendLoginRequest(login, p) << std::endl;
			} else if (type == "reg") {
				login = extractWord(str);
				UserName = login;
				std::cout << sendRegistrationRequest(login, n, sn, p, p) << std::endl;
			} else if (type == "logout") {
				std::cout << sendLogoutRequest() << std::endl;
			} else {
				std::cout << sendMessageToUser(type, str) << std::endl;
			}
		}
	private:
		void session();
		void closeConnection();

		String sendUserListRequest();
		String sendPendingMessagesRequest();
		String sendMessage(String& msg, const String& msgType);

		void processMessage(String&);
		void processPlainMessage(String&);
		void processLoginRespond(String&);
		void processLogoutRespond(String&);
		void processRegistrationRespond(String&);
		void processUserChangedRespond(String&);
		void processUserListRespond(String&);

		bool checkLoginPassword(const String& login, const String& password) const;
		bool checkNames(const String&, const String&) const;
		bool checkPasswords(const String& password1, const String& password2) const;

		UserIter find(const String&);
		UserIter find(User&);

		void updateMessageWindow(const UserIter&);
		void updateMessageWindow(const Users&);

		Client& c;
		Users users;
		String UserName;
		LoginWindow *loginWindow;
		RegistrationWindow *registrationWindow;
		MessageWindow *messageWindow;
		ExtractWord extractWord;
		std::shared_ptr<InputReader> inReaderPtr;
		DBController dbcontroller;
};

#endif
