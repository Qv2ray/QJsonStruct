#include "header.hpp"
#include "testform.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestForm f;
    f.show();

    return app.exec();
}
