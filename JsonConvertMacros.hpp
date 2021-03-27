#pragma once
#include "QJsonStructBase.hpp"

#ifndef _JSONSTRUCT_DEBUG
    #include <QJsonArray>
    #include <QJsonObject>
    #include <QList>
    #include <QMetaProperty>
    #include <QVariant>
#endif

#define __TOJSON_B(base) JsonStructHelper::MergeJson(___json_object_, base::toJson());
#define __TOJSON_F(name)                                                                                                                             \
    if (this->metaObject()->property(this->metaObject()->indexOfProperty(#name)).isRequired() ||                                                     \
        !(this->property(#name).value<decltype(QJSONSTRUCT_FIELD(name))>() == this->__default__##name))                                              \
    {                                                                                                                                                \
        ___json_object_.insert(#name, JsonStructHelper::Serialize(QJSONSTRUCT_FIELD(name)));                                                         \
    }

#define __FROMJSON_B(base) base::loadJson(___json_object_);
#define __FROMJSON_F(name)                                                                                                                           \
    if (___json_object_.toObject().contains(#name))                                                                                                  \
        JsonStructHelper::Deserialize(this->_##name, ___json_object_.toObject()[#name]);                                                             \
    else                                                                                                                                             \
        this->_##name = this->__default__##name;                                                                                                     \
    on_##name##_changed(this->_##name);

// ========================================================================================================= Public

#define JS_JSON_BF(_, b, f)                                                                                                                          \
    QJsonObject toJson() const                                                                                                                       \
    {                                                                                                                                                \
        QJsonObject ___json_object_;                                                                                                                 \
        FOREACH_CALL_FUNC(__TOJSON_B, ESC b)                                                                                                         \
        FOREACH_CALL_FUNC(__TOJSON_F, ESC f)                                                                                                         \
        return ___json_object_;                                                                                                                      \
    }                                                                                                                                                \
    void loadJson(const QJsonValue &___json_object_)                                                                                                 \
    {                                                                                                                                                \
        FOREACH_CALL_FUNC(FROMJSON_B, ESC b)                                                                                                         \
        FOREACH_CALL_FUNC(FROMJSON_F, ESC f)                                                                                                         \
    }

#define JS_JSON_F(_, b, f)                                                                                                                           \
    QJsonObject toJson() const                                                                                                                       \
    {                                                                                                                                                \
        QJsonObject ___json_object_;                                                                                                                 \
        FOREACH_CALL_FUNC(__TOJSON_F, ESC f)                                                                                                         \
        return ___json_object_;                                                                                                                      \
    }                                                                                                                                                \
    void loadJson(const QJsonValue &___json_object_)                                                                                                 \
    {                                                                                                                                                \
        FOREACH_CALL_FUNC(__FROMJSON_F, ESC f)                                                                                                       \
    }

class JsonStructHelper
{
  public:
    static void MergeJson(QJsonObject &mergeTo, const QJsonObject &mergeIn)
    {
        for (const auto &key : mergeIn.keys())
            mergeTo[key] = mergeIn.value(key);
    }

#define LOAD_SIMPLE_FUNC(type, convert_func)                                                                                                         \
    static void Deserialize(type &t, const QJsonValue &d)                                                                                            \
    {                                                                                                                                                \
        t = d.convert_func;                                                                                                                          \
    }

    LOAD_SIMPLE_FUNC(QString, toString());
    LOAD_SIMPLE_FUNC(QChar, toVariant().toChar());
    LOAD_SIMPLE_FUNC(std::string, toString().toStdString());
    LOAD_SIMPLE_FUNC(std::wstring, toString().toStdWString());
    LOAD_SIMPLE_FUNC(bool, toBool());
    LOAD_SIMPLE_FUNC(double, toDouble());
    LOAD_SIMPLE_FUNC(float, toVariant().toFloat());
    LOAD_SIMPLE_FUNC(int, toInt());
    LOAD_SIMPLE_FUNC(long, toVariant().toLongLong());
    LOAD_SIMPLE_FUNC(long long, toVariant().toLongLong());
    LOAD_SIMPLE_FUNC(unsigned int, toVariant().toUInt());
    LOAD_SIMPLE_FUNC(unsigned long, toVariant().toULongLong());
    LOAD_SIMPLE_FUNC(unsigned long long, toVariant().toULongLong());

#undef LOAD_SIMPLE_FUNC

    template<typename T>
    static void Deserialize(QList<T> &t, const QJsonValue &d)
    {
        t.clear();
        for (const auto &val : d.toArray())
        {
            T data;
            Deserialize(data, val);
            t.push_back(data);
        }
    }

    template<typename T>
    static void Deserialize(QStringList &t, const QJsonValue &d)
    {
        t.clear();
        for (const auto &val : d.toArray())
        {
            T data;
            Deserialize(data, val);
            t.push_back(data);
        }
    }

    template<typename TKey, typename TValue>
    static void Deserialize(QMap<TKey, TValue> &t, const QJsonValue &d)
    {
        t.clear();
        const auto &jsonObject = d.toObject();
        TKey keyVal;
        TValue valueVal;
        for (const auto &key : jsonObject.keys())
        {
            Deserialize(keyVal, key);
            Deserialize(valueVal, jsonObject.value(key));
            t.insert(keyVal, valueVal);
        }
    }

    template<typename T>
    static void Deserialize(T &t, const QJsonValue &d)
    {
        if constexpr (std::is_enum_v<T>)
            t = (T) d.toInt();
        else if constexpr (std::is_same_v<T, QJsonObject>)
            t = d.toObject();
        else if constexpr (std::is_same_v<T, QJsonArray>)
            t = d.toArray();
        else
            t.loadJson(d);
    }

    // =========================== Store Json Data ===========================

#define STORE_SIMPLE_FUNC(type)                                                                                                                      \
    static QJsonValue Serialize(const type &t)                                                                                                       \
    {                                                                                                                                                \
        return QJsonValue(t);                                                                                                                        \
    }
    STORE_SIMPLE_FUNC(int);
    STORE_SIMPLE_FUNC(bool);
    STORE_SIMPLE_FUNC(QJsonArray);
    STORE_SIMPLE_FUNC(QJsonObject);
    STORE_SIMPLE_FUNC(QString);
    STORE_SIMPLE_FUNC(long long);
    STORE_SIMPLE_FUNC(float);
    STORE_SIMPLE_FUNC(double);

#undef STORE_SIMPLE_FUNC

#define STORE_VARIANT_FUNC(type, func)                                                                                                               \
    static QJsonValue Serialize(const type &t)                                                                                                       \
    {                                                                                                                                                \
        return QJsonValue::fromVariant(func);                                                                                                        \
    }

    STORE_VARIANT_FUNC(std::string, QString::fromStdString(t))
    STORE_VARIANT_FUNC(std::wstring, QString::fromStdWString(t))
    STORE_VARIANT_FUNC(long, QVariant::fromValue<long>(t))
    STORE_VARIANT_FUNC(unsigned int, QVariant::fromValue<unsigned int>(t))
    STORE_VARIANT_FUNC(unsigned long, QVariant::fromValue<unsigned long>(t))
    STORE_VARIANT_FUNC(unsigned long long, QVariant::fromValue<unsigned long long>(t))

#undef STORE_VARIANT_FUNC

    template<typename TValue>
    static QJsonValue Serialize(const QMap<QString, TValue> &t)
    {
        QJsonObject mapObject;
        for (const auto &key : t.keys())
        {
            auto valueVal = Serialize(t.value(key));
            mapObject.insert(key, valueVal);
        }
        return mapObject;
    }

    template<typename T>
    static QJsonValue Serialize(const QList<T> &t)
    {
        QJsonArray listObject;
        for (const auto &item : t)
        {
            listObject.push_back(Serialize(item));
        }
        return listObject;
    }

    template<typename T>
    static QJsonValue Serialize(const T &t)
    {
        if constexpr (std::is_enum_v<T>)
            return (int) t;
        else if constexpr (std::is_same_v<T, QJsonObject> || std::is_same_v<T, QJsonArray>)
            return t;
        else
            return t.toJson();
    }
};
