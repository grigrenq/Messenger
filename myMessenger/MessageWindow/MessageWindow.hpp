#include <QMainWindow>
//#include <Controller>
#include <QWidget>
#include <QLayout>
#include <list>
#include <string>

class MessageWindow:public QMainWindow
{
private:
	Client client;
	list<Avatar> avatars;
	void createAvatar(Client&);
	void createMessages(client.messages);
	void updateAvatar(Client&);
	void updateMessages(client.messages);
	void addAvatar(Client&);
	void deleteMessages();
public:
	MessageWindow();
	void update(list<client>&);	
};

