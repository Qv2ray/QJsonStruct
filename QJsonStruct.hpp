#pragma once

#include "CompareMacros.hpp"
#include "JsonConvertMacros.hpp"

JS_MACRO_ARGUMENT_NO_WARN
#include <QMutex>
#include <QProperty>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#error "QJsonStruct does not support Qt version lesser than 6.0.0."
#endif

#define _QJS_PROP_OPTIONAL
#define _QJS_PROP_REQUIRED REQUIRED

// ========================================================================================================
//
// QJsonStruct Public APIS
//
// ========================================================================================================

//  QProperty<TYPE> p##NAME = QProperty<TYPE>([this]() { return JS_F(NAME); });
// this->p##NAME.markDirty();

template<typename, typename = void>
constexpr bool is_type_complete_v = false;

template<typename T>
constexpr bool is_type_complete_v<T, std::void_t<decltype(sizeof(T))>> = true;

template<typename T>
struct QJS_Prop
{
  private:
    T realValue;
    QProperty<T> pRealValue = QProperty<T>{ [this]() { return realValue; } };

  public:
    QJS_Prop() : realValue(), defaultValue(){};
    QJS_Prop(const T &value) : realValue(value), defaultValue(value){};
    QJS_Prop(const QJS_Prop<T> &value) : realValue(value.realValue), defaultValue(value.defaultValue){};

    const T defaultValue;
    bool isDefault() const
    {
        return realValue == defaultValue;
    }

    QProperty<T> &property()
    {
        return pRealValue;
    }

    void operator=(const T &v)
    {
        realValue = v;
        pRealValue.markDirty();
    }

    void operator=(const QJS_Prop<T> &v)
    {
        realValue = v.realValue;
        pRealValue.markDirty();
    }

    operator T() const
    {
        return realValue;
    }

    bool operator==(const T &right) const
    {
        return realValue == right;
    }
    bool operator!=(const T &right) const
    {
        return !(realValue == right);
    }
    bool operator==(const QJS_Prop<T> &right) const
    {
        return realValue == right.realValue;
    }
    bool operator!=(const QJS_Prop<T> &right) const
    {
        return !(realValue == right.realValue);
    }

    // Indirection
    const T operator*() const
    {
        return realValue;
    }
    T &operator*()
    {
        return realValue;
    }

    // Function call
    const T operator()() const
    {
        return realValue;
    }

    // Structure dereference
    const T *operator->() const
    {
        return &realValue;
    }
    T *operator->()
    {
        return &realValue;
    }

    QJsonValue toJson() const
    {
        return JsonStructHelper::Serialize(realValue);
    }

    void loadJson(const QJsonValue &val)
    {
        JsonStructHelper::Deserialize(realValue, val);
    }
    template<typename Y>
    void operator<<(const Y &another)
    {
        realValue << another;
    }
    template<typename Y>
    void operator>>(const Y &another)
    {
        return realValue >> another;
    }
    template<typename V>
    T operator+=(const V &v)
    {
        return realValue += v;
    }
    QJS_Prop<T> &operator++()
    {
        realValue++;
        return *this;
    }
};

#define QJS_PROP(TYPE, NAME, ...) QJS_PROP_D(TYPE, NAME, TYPE{}, __VA_ARGS__)
#define QJS_PROP_D(TYPE, NAME, DEFAULT, ...)                                                                                                         \
  public:                                                                                                                                            \
    QJS_Prop<TYPE> JS_F(NAME){ TYPE{ DEFAULT } };                                                                                                    \
    Q_PROPERTY(TYPE NAME MEMBER JS_F(NAME) __VA_ARGS__)

#define QJS_CONSTRUCTOR(CLASS, ...)                                                                                                                  \
    typedef CLASS this_type_t;                                                                                                                       \
                                                                                                                                                     \
  public:                                                                                                                                            \
    CLASS() __VA_ARGS__{};

#define QJS_FUNCTION(...) QJS_FUNC_JSON(__VA_ARGS__) QJS_FUNC_COMPARE(__VA_ARGS__)

#define QJS_RBINDING(source, source_prop, target, target_prop)                                                                                       \
    do                                                                                                                                               \
    {                                                                                                                                                \
        target->setProperty(#target_prop, source.source_prop.property().value());                                                                    \
        const auto lambda = [this]() { target->setProperty(#target_prop, source.source_prop.property().value()); };                                  \
        __qjs_binding_list.push_back(source.source_prop.property().onValueChanged(std::function{ lambda }));                                         \
    } while (false)

#define QJS_WBINDING(source, source_prop, target, target_prop, target_slot)                                                                          \
    do                                                                                                                                               \
    {                                                                                                                                                \
        connect(target, target_slot, [this]() {                                                                                                      \
            if (!__qjs_binding_lock.tryLock())                                                                                                       \
                return;                                                                                                                              \
            source.source_prop = target->target_prop();                                                                                              \
            __qjs_binding_lock.unlock();                                                                                                             \
        });                                                                                                                                          \
    } while (false)

#define QJS_RWBINDING(source, source_prop, target, target_prop, target_slot)                                                                         \
    QJS_RBINDING(source, source_prop, target, target_prop);                                                                                          \
    QJS_WBINDING(source, source_prop, target, target_prop, target_slot);

#define QJS_BINDING_HELPERS                                                                                                                          \
  private:                                                                                                                                           \
    typedef QPropertyChangeHandler<std::function<void()>> __qjs_binding_;                                                                            \
    QMutex __qjs_binding_lock;                                                                                                                       \
    std::list<__qjs_binding_> __qjs_binding_list;
#define QJS_CLEAR_BINDINGS __qjs_binding_list.clear();
