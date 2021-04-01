#pragma once
#include "QJsonStruct.hpp"

#include <QBindable>
#include <QObject>

struct ChildObject
{
    Q_GADGET
  public:
    QJS_CONSTRUCTOR(ChildObject)

    QJS_PROP(QString, childString, "", OPTIONAL)
    QJS_PROP(int, childInt, 0, REQUIRED)

    QJS_FUNCTION(F(childString, childInt))
};

struct myStruct
{
    Q_GADGET
    typedef QMap<QString, QString> stringmap;

  public:
    QJS_CONSTRUCTOR(myStruct)

    QJS_PROP(int, x, 0, REQUIRED)
    QJS_PROP(QString, string, "vstring", REQUIRED)
    QJS_PROP(QList<QString>, stringlist, QList<QString>{}, OPTIONAL)
    QJS_PROP(stringmap, map, stringmap{}, OPTIONAL)
    QJS_PROP(ChildObject, child, ChildObject{}, REQUIRED)

    QJS_FUNCTION(F(x, string, stringlist))
};
