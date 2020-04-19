#include "QJsonStruct.hpp"
#include "test.hpp"

#include <QCoreApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //
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
    TestStruct t;
    t.loadJson({ { "str", "data" } });
    auto s = t.str;
    //
    return app.exec();
}
