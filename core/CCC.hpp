#ifndef CCC_HPP
#define CCC_HPP


//#include "Controller.hpp"                                                                                     

class UserPtr{                                                                                                
	public:                                                                                                       
		//using ClientUser = MainWindow::User;                                                                    
		using ClientUser = Controller::User;                                                                      

		UserPtr()                                                                                                 
			: p_(nullptr) {}                                                                                      
		UserPtr(ClientUser* p)                                                                                    
			: p_(p) {}
		UserPtr(const UserPtr& u)                                                                                 
			: p_(u.p_) {} 

		ClientUser& operator*() { return *p_; }                                                                   
	private:                                                                                                      
		ClientUser* p_;                                                                                           
};

#endif
