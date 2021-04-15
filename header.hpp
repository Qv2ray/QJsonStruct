#pragma once
#include "QJsonStruct.hpp"

#include <QBindable>
#include <QObject>

struct ChildObject
{
    Q_GADGET
  public:
    QJS_CONSTRUCTOR(ChildObject)

    QJS_PROP_D(QString, childString, "")
    QJS_PROP_D(int, childInt, 0, REQUIRED)

    QJS_FUNCTION(F(childString, childInt))
};

class myStruct
{
    Q_GADGET
    typedef QMap<QString, QString> stringmap;

  public:
    QJS_CONSTRUCTOR(myStruct)

    QJS_PROP_D(int, x, 0, REQUIRED)
    QJS_PROP_D(QString, string, "vstring", REQUIRED)
    QJS_PROP(QList<QString>, stringlist)
    QJS_PROP(stringmap, map)
    QJS_PROP(ChildObject, child)

    QJS_FUNCTION(F(x, string, stringlist))
};
