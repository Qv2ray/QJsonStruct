#pragma once
#include "macroexpansion.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QVariant>

class JsonStruct
{
  public:
    static std::function<void(const QString &)> logger;
    //
    template<typename T>
    static void loadData(T &t, const QJsonValue &d)
    {
        t.loadJson(d.toObject());
    }
    static void loadData(QString &t, const QJsonValue &d)
    {
        t = d.toString();
    }
    static void loadData(bool &t, const QJsonValue &d)
    {
        t = d.toBool();
    }
    static void loadData(int &t, const QJsonValue &d)
    {
        t = d.toInt();
    }
    static void loadData(double &t, const QJsonValue &d)
    {
        t = d.toDouble();
    }
    static void loadData(long &t, const QJsonValue &d)
    {
        t = d.toVariant().toLongLong();
    }
    static void loadData(unsigned int &t, const QJsonValue &d)
    {
        t = d.toVariant().toUInt();
    }
    static void loadData(unsigned long &t, const QJsonValue &d)
    {
        t = d.toVariant().toULongLong();
    }
    static void loadData(float &t, const QJsonValue &d)
    {
        t = d.toVariant().toFloat();
    }

    template<typename T>
    static void loadData(QList<T> &t, const QJsonValue &d)
    {
        t.clear();
        for (const auto &val : d.toArray())
        {
            T data;
            loadData(data, val);
            t.push_back(data);
        }
    }

    template<typename TKey, typename TValue>
    static void loadData(QMap<TKey, TValue> &t, const QJsonValue &d)
    {
        t.clear();
        const auto &jsonObject = d.toObject();
        TKey keyVal;
        TValue valueVal;
        for (const auto &key : jsonObject.keys())
        {
            loadData(keyVal, key);
            loadData(valueVal, jsonObject.value(key));
            t.insert(keyVal, valueVal);
        }
    }
};

inline std::function<void(const QString &)> JsonStruct::logger = {};

#define CONVERT_FUNC_DECL(name) JsonStruct::loadData(this->name, o[#name]);

#define QSTRUCT_REGISTER(classType, ...)                                                                                                        \
    void loadJson(const QJsonObject &o)                                                                                                         \
    {                                                                                                                                           \
        FOREACH_CALL_FUNC(CONVERT_FUNC_DECL, __VA_ARGS__)                                                                                       \
    }                                                                                                                                           \
    [[nodiscard]] static classType fromJson(const QJsonObject &o)                                                                               \
    {                                                                                                                                           \
        classType _t;                                                                                                                           \
        _t.loadJson(o);                                                                                                                         \
        return _t;                                                                                                                              \
    }
