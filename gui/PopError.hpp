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
 *  @brief ....  
 */  
class PopError : public QWidget
{
    Q_OBJECT

    public:
        using String = std::string;

	   
        /** 
        *   @brief  ....    
        *   @param  .... 
  	*/       
	PopError();

	/** 
        *   @brief  ....    
        *   @param  ... 
  	*   @return void
  	*/  
        void handleConnection();
        
	/** 
        *   @brief  ....    
        *   @param  .... 
  	*   @return void
  	*/  
	void setText(const String&);

	/** 
        *   @brief  .....    
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
