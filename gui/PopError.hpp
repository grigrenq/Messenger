/** 
 *  @file    PopError.hpp
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0   
 *  @brief ....
 */
#ifndef POPERROR_HPP
#define POPERROR_HPP

#include <string>
#include <QWidget>
#include <QMessageBox>
#include <QObject>

class QPushButton;



 /**
 *  @brief class for creating message box, thats show kind of errors
 */  
class PopError : public QWidget
{
    Q_OBJECT

    public:
        using String = std::string;

	   
        /** 
        *   @brief  PopError constructor for class PopError, thats create message box   
        *   @param  no parametrs 
  	*/       
	PopError();

	/** 
        *   @brief  handleConnection to merge the mesagebox and the type of the error with the slots
        *   @param  no parametrs
  	*   @return void
  	*/  
        void handleConnection();
        
	/** 
        *   @brief  setText added kind of error in string and  emited signal for adding message in message box
        *   @param  const String&  ???
  	*   @return void
  	*/  
	void setText(const String&);

	/** 
        *   @brief  execute showed message box
        *   @param  no parametrs 
  	*   @return void
  	*/  
        void execute();
   
    public slots:
        void setTextSlot(const QString&);
        void executeSlot();
    
    signals:
        void setTextSignal(const QString&);
        void executeSignal();
    
    private:
        void createMessageBox();
        QMessageBox* messageBox;
};
#endif
