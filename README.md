                               GRI Messenger

Project consists of following directories, each of which has it's own Makefile.
To run project's server , make Makefile in core directory,  run the generated executable file using following command: ./run. 

Next, to run project's user, make Makefile in gui directory, run the generated executable file using following command: ./gui.

Testing can be accomplished either via GUI or terminal.
 
In terminal type “log login”, after which a login request is sent to server with typed login and default password(ex. log Martijn32). 
For registration type “reg login”, after which a registration request is sent to server with typed login and default password, name and surname(ex. reg Martijn32).
For logging out type “logout”,  after which a logout request is sent to server.
In order to send messages to another user type “receivers’ login message”
(ex. Martijn32 Hello Martijn32, how are you doing?).

First the login window is opened, on users press “CREATE NEW ACCOUNT”, after which the registration window is opened, on which users enter their login, password, name and surname to and press “SignUp” to complete the registration procedure.
On login window users must enter their login and password and press “LogIn” to log in.
Finally, after successfully logging in the main window is opened, on which users choose corresponding user from user list, write message in writing area and press “Send” button.
  
