#pragma once
#include "QJsonStruct.hpp"
#ifndef _X
    #include <QList>
    #include <QString>
    #include <QStringList>
#endif

struct BaseStruct
{
    QString baseStr;
    int o;
    JSONSTRUCT_REGISTER(BaseStruct, F(baseStr, o))
};

struct TestInnerStruct : BaseStruct
{
    QString str;
    JSONSTRUCT_REGISTER(TestInnerStruct, B(BaseStruct), F(str))
};

struct TestStruct
{
    QString str;
    QList<int> listOfNumber;
    QList<bool> listOfBool;
    QList<QString> listOfString;
    QList<QList<QString>> listOfListOfString;

    QMap<QString, QString> map;
    TestInnerStruct inner;

    JSONSTRUCT_REGISTER(TestStruct, F(str, listOfNumber, listOfBool, listOfString, listOfListOfString, map, inner));

    TestStruct()
    {
    }
};
