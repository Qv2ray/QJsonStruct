#pragma once
#include "QJsonStruct.hpp"

#include <QBindable>
#include <QObject>

struct ChildObject : public QObject
{
    Q_OBJECT
  public:
    QJS_CONSTRUCTOR(ChildObject)

    QJS_PROP_D(QString, childString, "")
    QJS_PROP_D(int, childInt, 0, REQUIRED)

    QJS_FUNCTION(F(childString, childInt))
};

class myStruct : public QObject
{
    Q_OBJECT
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
