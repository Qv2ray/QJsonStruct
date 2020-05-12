#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <tuple>

class QJsonIO
{
  public:
    template<typename current_key_type, typename... t_other_types>
    static QJsonValue GetValue(const QJsonValue &parent, const current_key_type &current, const t_other_types &... other)
    {
        if constexpr (sizeof...(t_other_types) == 0)
            return parent;
        else if constexpr (std::is_same<current_key_type, QJsonArray::size_type>::value)
            return GetValue(parent.toArray()[current], other...);
        else
            return GetValue(parent.toObject()[current], other...);
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
        else
        {
            using next_key_type = typename std::tuple_element<0, std::tuple<t_other_key_types...>>::type;

            // Means we still have many keys
            if constexpr (std::is_same<next_key_type, QJsonArray::size_type>::value)
            {
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
    }
};
