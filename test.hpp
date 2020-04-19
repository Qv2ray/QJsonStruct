#pragma once
#include "QJsonStruct.hpp"

#include <QList>
#include <QString>
#include <QStringList>

struct BaseStruct
{
    QString baseStr;
    QSTRUCT_REGISTER(BaseStruct, baseStr)
};

struct TestInnerStruct : BaseStruct
{
    QString str;
    QSTRUCT_REGISTER(TestInnerStruct, str, baseStr)
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

    QSTRUCT_REGISTER(TestStruct, map, listOfBool, str, listOfString, listOfNumber, listOfListOfString, inner);

    TestStruct()
    {
    }
};
