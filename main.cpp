#include "header.hpp"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    MyObject2 o2;
    o2.xxx().set_xx(1);
    o2.lists().append("Test");
    const auto j = o2.toJson();

    const auto o22 = o2;

    return 0;
}
