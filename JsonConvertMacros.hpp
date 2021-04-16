#pragma once
#include "QJsonStructBase.hpp"
#include "macroexpansion.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QMetaProperty>
#include <QVariant>

// ============================================================================================
// Load JSON Wrapper
#define _QJS_FROM_JSON_F(...) FOR_EACH_2(__FROMJSON_F, __VA_ARGS__)
#define _QJS_FROM_JSON_B(...) FOR_EACH_2(__FROMJSON_B, __VA_ARGS__)
#define _QJS_FROM_JSON_BF(option) _QJS_FROM_JSON_##option

// ============================================================================================
// To JSON Wrapper
#define _QJS_TO_JSON_F(...) FOR_EACH_2(__TOJSON_F, __VA_ARGS__)
#define _QJS_TO_JSON_B(...) FOR_EACH_2(__TOJSON_B, __VA_ARGS__)
#define _QJS_TO_JSON_BF(option) _QJS_TO_JSON_##option
// =========================================================================================================

#define __TOJSON_B(base) JsonStructHelper::MergeJson(___json_object_, base::toJson());
#define __TOJSON_F(name)                                                                                                                             \
    if (staticMetaObject.property(staticMetaObject.indexOfProperty(#name)).isRequired() || !name.isDefault())                                        \
    {                                                                                                                                                \
        ___json_object_.insert(#name, JsonStructHelper::Serialize(this->JS_F(name)));                                                                \
    }

#define __FROMJSON_B(name) name::loadJson(___json_object_);
#define __FROMJSON_F(name)                                                                                                                           \
    if (___json_object_.toObject().contains(#name))                                                                                                  \
    {                                                                                                                                                \
        JsonStructHelper::Deserialize(this->JS_F(name), ___json_object_.toObject()[#name]);                                                          \
    }

// this->p##name.markDirty();

// ========================================================================================================= Public

#define QJS_FUNC_JSON(CLASS, ...)                                                                                                                    \
  public:                                                                                                                                            \
    QJsonObject toJson() const                                                                                                                       \
    {                                                                                                                                                \
        QJsonObject ___json_object_;                                                                                                                 \
        FOR_EACH(_QJS_TO_JSON_BF, __VA_ARGS__);                                                                                                      \
        return ___json_object_;                                                                                                                      \
    }                                                                                                                                                \
    void loadJson(const QJsonValue &___json_object_)                                                                                                 \
    {                                                                                                                                                \
        FOR_EACH(_QJS_FROM_JSON_BF, __VA_ARGS__);                                                                                                    \
    }                                                                                                                                                \
    CLASS(const QJsonObject &json)                                                                                                                   \
    {                                                                                                                                                \
        loadJson(json);                                                                                                                              \
    }

// ========================================================================================================= Plain JSON
#define __TOJSON_PLAIN_F(name) ___json_object_.insert(#name, JsonStructHelper::Serialize(this->name));
#define __FROMJSON_PLAIN_F(name)                                                                                                                     \
    if (___json_object_.toObject().contains(#name))                                                                                                  \
        JsonStructHelper::Deserialize(this->name, ___json_object_.toObject()[#name]);

#define QJS_PLAIN_JSON(...)                                                                                                                          \
  public:                                                                                                                                            \
    QJsonObject toJson() const                                                                                                                       \
    {                                                                                                                                                \
        QJsonObject ___json_object_;                                                                                                                 \
        FOR_EACH(__TOJSON_PLAIN_F, __VA_ARGS__)                                                                                                      \
        return ___json_object_;                                                                                                                      \
    }                                                                                                                                                \
    void loadJson(const QJsonValue &___json_object_)                                                                                                 \
    {                                                                                                                                                \
        FOR_EACH(__FROMJSON_PLAIN_F, __VA_ARGS__)                                                                                                    \
    }

namespace QJsonStruct
{
    template<typename T>
    inline void ExternalDeserializer(T &t, const QJsonValue &d)
    {
        t.loadJson(d);
    }
    template<typename T>
    inline QJsonValue ExternalSerializer(const T &t)
    {
        return t.toJson();
    }
} // namespace QJsonStruct

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
            QJsonStruct::ExternalDeserializer<T>(t, d);
    }

    // =========================== Store Json Data ===========================

#define STORE_SIMPLE_FUNC(type)                                                                                                                      \
    static QJsonValue Serialize(const type &t)                                                                                                       \
    {                                                                                                                                                \
        return { t };                                                                                                                                \
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
            return QJsonStruct::ExternalSerializer<T>(t);
    }
};
