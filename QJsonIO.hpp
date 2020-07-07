#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <tuple>

class QJsonIO
{
  public:
    const static inline auto Null = QJsonValue(QJsonValue::Null);
    const static inline auto Undefined = QJsonValue(QJsonValue::Undefined);
    template<typename current_key_type, typename... t_other_types>
    static QJsonValue GetValue(const QJsonValue &parent, const current_key_type &current, const t_other_types &... other)
    {
        if constexpr (sizeof...(t_other_types) == 0)
            return parent[current];
        else if constexpr (std::is_same<current_key_type, QJsonArray::size_type>::value)
            return GetValue(parent.toArray()[current], other...);
        else
            return GetValue(parent.toObject()[current], other...);
    }

    template<typename... key_types_t>
    static QJsonValue GetValue(QJsonValue value, const std::tuple<key_types_t...> &keys, const QJsonValue &defaultValue = Undefined)
    {
        std::apply([&](auto &&... args) -> void { ((value = value[args]), ...); }, keys);
        return value.isUndefined() ? defaultValue : value;
    }

    //
    // ========= Set Values =========
    //
    template<typename parent_type, typename t_value_type, typename current_key_type, typename... t_other_key_types>
    static void SetValue(parent_type &parent, const t_value_type &val, const current_key_type &current, const t_other_key_types &... other)
    {
        // If current parent is an array, increase its size to fit the "key"
        if constexpr (std::is_same<current_key_type, QJsonArray::size_type>::value)
            for (auto i = parent.size(); i <= current; i++) parent.insert(i, {});

        // If the t_other_key_types has nothing....
        // Means we have reached the end of recursion.
        if constexpr (sizeof...(t_other_key_types) == 0)
            parent[current] = val;
        else if constexpr (std::is_same<typename std::tuple_element<0, std::tuple<t_other_key_types...>>::type, QJsonArray::size_type>::value)
        {
            // Means we still have many keys
            // So this element is an array.
            auto _array = parent[current].toArray();
            SetValue(_array, val, other...);
            parent[current] = _array;
        }
        else
        {
            auto _object = parent[current].toObject();
            SetValue(_object, val, other...);
            parent[current] = _object;
        }
    }
};
