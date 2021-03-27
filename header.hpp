#pragma once

#include "QJsonStruct.hpp"

class x : public QObject
{
    Q_OBJECT
  public:
    JS_PROP_O(int, xx, 114)
    JS_PROP_M(int, xy, 514)
    JS_REGISTER(x, (), (xx, xy), JSON_F, CCTOR, DCTOR, COMPARE_F)
};

Q_DECLARE_METATYPE(x)

class MyObject2 : public QObject
{
    Q_OBJECT
    JS_PROP_O(x, xxx, x{})
    JS_PROP_O(QList<QString>, lists, QStringList{})
    JS_REGISTER(MyObject2, (), (xxx, lists), JSON_F, CCTOR, DCTOR, COMPARE_F)
};
