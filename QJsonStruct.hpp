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

template<typename T>
struct QJS_Prop
{
    virtual ~QJS_Prop() = default;
    // clang-format off
    virtual operator       T&()       { return value; }
    virtual operator const T&() const { return value; }
    //
    virtual       T* operator->()       { return &value; }
    virtual const T* operator->() const { return &value; }
    virtual       T& operator()()       { return  value; }
    virtual const T& operator()() const { return  value; }
    //
    virtual T& operator=(const T& f)           { value = f;       pRealValue.markDirty(); return value; }
    virtual T& operator=(const QJS_Prop<T> &v) { value = v.value; pRealValue.markDirty(); return value; }
    // clang-format on

  private:
    T value;
    QProperty<T> pRealValue{ [this]() { return value; } };

  public:
    QJS_Prop() : value(), defaultValue(){};
    QJS_Prop(const T &val) : value(val), defaultValue(val){};
    QJS_Prop(const QJS_Prop<T> &val) : value(val.value), defaultValue(val.defaultValue){};

    const T defaultValue;
    bool isDefault() const
    {
        return value == defaultValue;
    }

    QProperty<T> &property()
    {
        return pRealValue;
    }

    bool operator==(const T &right) const
    {
        return value == right;
    }
    bool operator!=(const T &right) const
    {
        return !(value == right);
    }
    bool operator==(const QJS_Prop<T> &right) const
    {
        return value == right.value;
    }
    bool operator!=(const QJS_Prop<T> &right) const
    {
        return !(value == right.value);
    }

    // Indirection
    const T operator*() const
    {
        return value;
    }
    T &operator*()
    {
        return value;
    }

    QJsonValue toJson() const
    {
        return JsonStructHelper::Serialize(value);
    }

    void loadJson(const QJsonValue &val)
    {
        JsonStructHelper::Deserialize(value, val);
    }
    template<typename Y>
    void operator<<(const Y &another)
    {
        value << another;
    }
    template<typename Y>
    void operator>>(const Y &another)
    {
        return value >> another;
    }
    template<typename V>
    T operator+=(const V &v)
    {
        return value += v;
    }
    QJS_Prop<T> &operator++()
    {
        value++;
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

#define QJS_RBINDING(source_prop, target, target_prop)                                                                                               \
    do                                                                                                                                               \
    {                                                                                                                                                \
        target->setProperty(#target_prop, source_prop.property().value());                                                                           \
        const auto lambda = [&]() { target->setProperty(#target_prop, source_prop.property().value()); };                                            \
        __qjs_binding_list.push_back(source_prop.property().onValueChanged(std::function{ lambda }));                                                \
    } while (false)

#define QJS_WBINDING(source_prop, target, target_prop, target_slot)                                                                                  \
    do                                                                                                                                               \
    {                                                                                                                                                \
        connect(target, target_slot, [&]() {                                                                                                         \
            if (!__qjs_binding_lock.tryLock())                                                                                                       \
                return;                                                                                                                              \
            source_prop = target->target_prop();                                                                                                     \
            __qjs_binding_lock.unlock();                                                                                                             \
        });                                                                                                                                          \
    } while (false)

#define QJS_RWBINDING(source_prop, target, target_prop, target_slot)                                                                                 \
    QJS_RBINDING(source_prop, target, target_prop);                                                                                                  \
    QJS_WBINDING(source_prop, target, target_prop, target_slot);

#define QJS_BINDING_CLEAR __qjs_binding_list.clear();
#define QJS_BINDING_HELPERS                                                                                                                          \
  private:                                                                                                                                           \
    typedef QPropertyChangeHandler<std::function<void()>> __qjs_binding_;                                                                            \
    QMutex __qjs_binding_lock;                                                                                                                       \
    std::list<__qjs_binding_> __qjs_binding_list;
