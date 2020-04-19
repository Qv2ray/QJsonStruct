#pragma once
#include "QJsonStruct.hpp"

#include <QList>
#include <QString>
#include <QStringList>

struct BaseStruct
{
    QString baseStr;
    int o;
    QSTRUCT_REGISTER(BaseStruct, F(baseStr, o))
};

struct TestInnerStruct : BaseStruct
{
    QString str;
    QSTRUCT_REGISTER(TestInnerStruct, F(str, baseStr))
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

    QSTRUCT_REGISTER(TestStruct, F(str, listOfNumber, listOfBool, listOfString, listOfListOfString, map, inner));

    TestStruct()
    {
    }
};
