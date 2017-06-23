/** 
*  @file    Controller.hpp
*  @author  GRI Team
*  @date    06/22/2017  
*  @version 1.0   
*  @brief
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Client.hpp"
#include "ClientUser.hpp"
#include "InputValidator.hpp"
#include "DBController.hpp"
#include "TransportLayer.hpp"

#include <memory>

class LoginWindow;
class MainWindow;
class PopError;


void* readMessage(void*);
void* handleSession(void*);


class Controller
{
public:
	using User = ClientUser;
	using UserPtr = std::shared_ptr<User>;
	using Users = std::list<UserPtr>;
	using UserIter = Users::iterator;
	using String = User::String;

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
				return nullptr;
			}
			bool stopRequested() const {
				return stopReading;
			}
			private:
				Controller &controller;
				pthread_t pth;
				bool stopReading;
		};//InputReader

	
		Controller(Client&);
		void run(const String&);
		void handleSession();

		String sendLoginRequest(const String& login, const String& password);
		String sendLogoutRequest();
		String sendRegistrationRequest(const String& login, const String& name,
				const String& surname, const String& password);
		String sendMessageToUser(const String& toUser, String& msg);
		String sendConvRequest(const String&);

		void f(String& str)	//for testing
		{
			String n = "name";
			String sn = "surname";
			String p = "pass";

			String type = wordExtractor_(str, true, ' ');
			String l;

			//std::cout << "type=" << type << "." << str << ".\n";

			if (type == "log") {
				l = wordExtractor_(str);
				userLogin_ = l;
				std::cout << sendLoginRequest(l, p) << std::endl;
			} else if (type == "reg") {
				l = wordExtractor_(str);
				userLogin_ = l;
				std::cout << sendRegistrationRequest(l, n, sn, p) << std::endl;
			} else if (type == "logout") {
				std::cout << sendLogoutRequest() << std::endl;
			} else {
				std::cout << sendMessageToUser(type, str) << std::endl;
			}
		}

		String getLogin() const;
	private:
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
		void processConvRespond(String&);

		UserIter find(const String&);
		UserIter find(User&);

		void updateMainWindow(const UserIter&);
		void updateMainWindow();

		Client& c_;
		Users users_;
		String userLogin_;

		LoginWindow* loginWindow_;
		MainWindow* mainWindow_;
		PopError* popError_;

		WordExtractor wordExtractor_;
		TransportLayer transportLayer_;
		std::shared_ptr<InputReader> inReaderPtr;
		DBController<Users> dbcontroller_;
		InputValidator validator_;
		String login;
};

#endif
