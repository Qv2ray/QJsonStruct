#include "QJsonStruct.hpp"
#include "test.hpp"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QString>
#include <iostream>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    auto f = TestStruct::fromJson( //
        {
            { "inner", QJsonObject{ { "str", "innerString" }, { "baseStr", "baseInnerString" } } }, //
            { "str", "data1" },                                                                     //
            { "map", QJsonObject{ { "mapStr", "mapData" } } },                                      //
            { "listOfString", QJsonArray{ "1", "2", "3", "4", "5" } },                              //
            { "listOfNumber", QJsonArray{ 1, 2, 3, 4, 5 } },                                        //
            { "listOfBool", QJsonArray{ true, false, false, true, true } },                         //
            { "listOfListOfString", QJsonArray{ QJsonArray{ "1" },                                  //
                                                QJsonArray{ "1", "2" },                             //
                                                QJsonArray{ "1", "2", "3" },                        //
                                                QJsonArray{ "1", "2", "3", "4" },                   //
                                                QJsonArray{ "1", "2", "3", "4", "5" } } },          //
        });
    auto x = f.toJson();
    std::cout << QJsonDocument(x).toJson().toStdString() << std::endl;
    return 0;
}
