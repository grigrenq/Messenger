#include <QApplication>
#include "LoginWindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    LoginWindow lWin;
    lWin.show();
    return app.exec();
}

