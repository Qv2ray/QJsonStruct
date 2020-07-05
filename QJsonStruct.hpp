#pragma once
#include "macroexpansion.hpp"

#ifndef _X
    #include <QJsonArray>
    #include <QJsonObject>
    #include <QList>
    #include <QVariant>
#endif

template<class C>
class has_tojson_func
{
    template<class T>
    static std::true_type testSignature(QJsonObject (T::*)() const);

    template<class T>
    static decltype(testSignature(&T::toJson)) test(std::nullptr_t);

    template<class T>
    static std::false_type test(...);

  public:
    using type = decltype(test<C>(nullptr));
    static const bool value = type::value;
};

//
#define ___LOAD_JSON_CONVERT_F_FUNC(name) JsonStructHelper::___json_struct_load_data(this->name, ___json_object_[#name]);
//
#define ___LOAD_JSON_CONVERT_B_FUNC(...) FOREACH_CALL_FUNC_3(___LOAD_JSON_CONVERT_B_FUNC_IMPL, __VA_ARGS__)
#define ___LOAD_JSON_CONVERT_B_FUNC_IMPL(name) name::loadJson(___json_object_);
//
#define ___LOAD_JSON_CONVERT_FUNC_DECL_F(...) FOREACH_CALL_FUNC_2(___LOAD_JSON_CONVERT_F_FUNC, __VA_ARGS__)
#define ___LOAD_JSON_CONVERT_FUNC_DECL_B(...) FOREACH_CALL_FUNC_2(___LOAD_JSON_CONVERT_B_FUNC, __VA_ARGS__)
//
#define ___LOAD_JSON_EXTRACT_B_F(name_option) ___LOAD_JSON_CONVERT_FUNC_DECL_##name_option
//
// =====================
//
#define ___STORE_JSON_CONVERT_F_FUNC(name) ___json_object_.insert(#name, JsonStructHelper::___json_struct_store_data(name));
//
#define ___STORE_JSON_CONVERT_B_FUNC_IMPL(name) JsonStructHelper::__json_struct_merge_json(___json_object_, name::toJson());
#define ___STORE_JSON_CONVERT_B_FUNC(...) FOREACH_CALL_FUNC_3(___STORE_JSON_CONVERT_B_FUNC_IMPL, __VA_ARGS__)
//
//
#define ___STORE_JSON_CONVERT_FUNC_DECL_F(...) FOREACH_CALL_FUNC_2(___STORE_JSON_CONVERT_F_FUNC, __VA_ARGS__)
#define ___STORE_JSON_CONVERT_FUNC_DECL_B(...) FOREACH_CALL_FUNC_2(___STORE_JSON_CONVERT_B_FUNC, __VA_ARGS__)
//
#define ___STORE_JSON_EXTRACT_B_F(name_option) ___STORE_JSON_CONVERT_FUNC_DECL_##name_option

#define JSONSTRUCT_REGISTER(___class_type_, ...)                                                                                                \
    void loadJson(const QJsonValue &___json_object_)                                                                                            \
    {                                                                                                                                           \
        FOREACH_CALL_FUNC(___LOAD_JSON_EXTRACT_B_F, __VA_ARGS__);                                                                               \
    }                                                                                                                                           \
    [[nodiscard]] static auto fromJson(const QJsonValue &___json_object_)                                                                       \
    {                                                                                                                                           \
        ___class_type_ _t;                                                                                                                      \
        _t.loadJson(___json_object_);                                                                                                           \
        return _t;                                                                                                                              \
    }                                                                                                                                           \
    [[nodiscard]] const QJsonObject toJson() const                                                                                              \
    {                                                                                                                                           \
        QJsonObject ___json_object_;                                                                                                            \
        FOREACH_CALL_FUNC(___STORE_JSON_EXTRACT_B_F, __VA_ARGS__);                                                                              \
        return ___json_object_;                                                                                                                 \
    }

#define ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(type, convert_func)                                                                           \
    static void ___json_struct_load_data(type &t, const QJsonValue &d)                                                                          \
    {                                                                                                                                           \
        if (!d.isNull() && !d.isUndefined())                                                                                                    \
            t = d.convert_func();                                                                                                               \
    }
class JsonStructHelper
{
  public:
    static void __json_struct_merge_json(QJsonObject &mergeTo, const QJsonObject &mergeIn)
    {
        for (const auto &key : mergeIn.keys())
        {
            mergeTo[key] = mergeIn.value(key);
        }
    }
    //
    template<typename T>
    static void ___json_struct_load_data(T &t, const QJsonValue &d)
    {
        if constexpr (std::is_enum<T>::value)
            t = (T) d.toInt();
        else
            t.loadJson(d);
    }
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(QString, toString);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(std::string, toString().toStdString);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(std::wstring, toString().toStdWString);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(bool, toBool);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(double, toDouble);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(float, toVariant().toFloat);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(int, toInt);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(long, toVariant().toLongLong);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(long long, toVariant().toLongLong);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(unsigned int, toVariant().toUInt);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(unsigned long, toVariant().toULongLong);
    ___DECL_JSON_STRUCT_LOAD_SIMPLE_TYPE_FUNC(unsigned long long, toVariant().toULongLong);

    template<typename T>
    static void ___json_struct_load_data(QList<T> &t, const QJsonValue &d)
    {
        t.clear();
        for (const auto &val : d.toArray())
        {
            T data;
            ___json_struct_load_data(data, val);
            t.push_back(data);
        }
    }

    template<typename TKey, typename TValue>
    static void ___json_struct_load_data(QMap<TKey, TValue> &t, const QJsonValue &d)
    {
        t.clear();
        const auto &jsonObject = d.toObject();
        TKey keyVal;
        TValue valueVal;
        for (const auto &key : jsonObject.keys())
        {
            ___json_struct_load_data(keyVal, key);
            ___json_struct_load_data(valueVal, jsonObject.value(key));
            t.insert(keyVal, valueVal);
        }
    }
    // =========================== Store Json Data ===========================
#define ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(type)                                                                                        \
    static QJsonValue ___json_struct_store_data(const type &t)                                                                                  \
    {                                                                                                                                           \
        return QJsonValue(t);                                                                                                                   \
    }
    template<typename T>
    static QJsonValue ___json_struct_store_data(const T &t)
    {
        if constexpr (std::is_enum<T>::value)
            return (int) t;
        else
            return t.toJson();
    }
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(int);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(bool);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(QJsonArray);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(QJsonObject);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(QString);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(long long);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(float);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC(double);
    //
#define ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC_EXTRA(type)                                                                                  \
    static QJsonValue ___json_struct_store_data(const type &t)                                                                                  \
    {                                                                                                                                           \
        return QJsonValue((qint64) t);                                                                                                          \
    }
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC_EXTRA(long);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC_EXTRA(unsigned long);
    ___DECL_JSON_STRUCT_STORE_SIMPLE_TYPE_FUNC_EXTRA(unsigned long long);
    template<typename TValue>
    static QJsonValue ___json_struct_store_data(const QMap<QString, TValue> &t)
    {
        QJsonObject mapObject;
        for (const auto &key : t.keys())
        {
            auto valueVal = ___json_struct_store_data(t.value(key));
            mapObject.insert(key, valueVal);
        }
        return mapObject;
    }
    template<typename T>
    static QJsonValue ___json_struct_store_data(const QList<T> &t)
    {
        QJsonArray listObject;
        for (const auto &item : t)
        {
            listObject.push_back(___json_struct_store_data(item));
        }
        return listObject;
    }

    static void ____extract_json(QJsonObject &){};
    template<typename _tVAL, typename... _other>
    static void ____extract_json(QJsonObject &o, const QString &key, const _tVAL &value, const _other &... others)
    {
        if constexpr (has_tojson_func<_tVAL>::value)
        {
            o[key] = value.toJson();
        }
        else
        {
            o[key] = JsonStructHelper::___json_struct_store_data(value);
        }
        ____extract_json(o, others...);
    }
};

#define __EXTRACT(n) , #n, n
#define __CALL_X(json, ...) JsonStructHelper::____extract_json(json FOREACH_CALL_FUNC(__EXTRACT, __VA_ARGS__))
#define JSONSTRUCT_REGISTER_TOJSON(...)                                                                                                         \
    [[nodiscard]] QJsonObject toJson() const                                                                                                    \
    {                                                                                                                                           \
        QJsonObject ___json_object;                                                                                                             \
        __CALL_X(___json_object, __VA_ARGS__);                                                                                                  \
        return ___json_object;                                                                                                                  \
    }
