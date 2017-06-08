#include <QApplication>
#include "login_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    login_window l_win;
    l_win.show();
    return app.exec();
}
