/** 
 *  @file    PopError.hpp
 *  @author  GRI Team
 *  @date    06/23/2017  
 *  @version 1.0   
 *  @brief Contains PopError class which is inherited from QWidget class.
 */
#ifndef POPERROR_HPP
#define POPERROR_HPP

#include <string>
#include <QWidget>
#include <QMessageBox>
#include <QObject>

class QPushButton;



 /**
 *  @brief Class for creating popup window for some errors.
 */  
class PopError : public QWidget
{
    Q_OBJECT

    public:
        using String = std::string;

	   
        /** 
        *   @brief  Function for creating objects of type PopError.   
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
        *   @brief  Function for calling function that emits signal for setting text to message box.
        *   @param  The only parameter is const String&.
  	*   @return void
  	*/  
	void setText(const String&);

	/** 
        *   @brief  Function for executing(i.e showing) message box.
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
