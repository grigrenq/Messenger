#ifndef POPERROR_HPP
#define POPERROR_HPP

#include <string>
#include <QWidget>
#include <QMessageBox>
#include <QObject>

class QPushButton;

class PopError : public QWidget
{
    Q_OBJECT

    public:
        using String = std::string;

        PopError();
        void handleConnection();
        void setText(const String&);
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
