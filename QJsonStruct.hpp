#pragma once

#include "CompareMacros.hpp"
#include "JsonConvertMacros.hpp"

JS_MACRO_ARGUMENT_NO_WARN
#include <QMutex>
#include <QObject>
#include <QProperty>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #error "QJsonStruct does not support Qt version lesser than 6.0.0."
#endif

#define _QJS_PROP_OPTIONAL
#define _QJS_PROP_REQUIRED REQUIRED

#define _QJS_PROP_IMPL(TYPE, NAME, DEFAULT, ...)                                                                                                     \
  public:                                                                                                                                            \
    Q_SIGNAL void on_##NAME##_changed();                                                                                                             \
    QJS_Prop<TYPE> JS_F(NAME){ [this]() { on_##NAME##_changed(); }, TYPE{ DEFAULT } };                                                               \
    Q_PROPERTY(TYPE NAME MEMBER JS_F(NAME) NOTIFY on_##NAME##_changed __VA_ARGS__)
#define _QJS_CONSTRUCTOR_IMPL(CLASS, ...)                                                                                                            \
    using this_type_t = CLASS;                                                                                                                       \
                                                                                                                                                     \
  public:                                                                                                                                            \
    CLASS() __VA_ARGS__{};                                                                                                                           \
    CLASS(const CLASS &another)                                                                                                                      \
    {                                                                                                                                                \
        *this = another;                                                                                                                             \
    }

// ========================================================================================================
//
// QJsonStruct Public APIS
//
// ========================================================================================================

template<typename T>
struct QJS_Prop
{
  public:
    // clang-format off
    virtual       T* operator->()       { return &value; }
    virtual const T* operator->() const { return &value; }

    virtual       T& operator()()       { return value; }
    virtual const T& operator()() const { return value; }

    virtual const T  operator*()  const { return value; }
    virtual       T& operator*()        { return value; }

    virtual operator       T&()         { return value; }
    virtual operator const T&()   const { return value; }

    virtual           T& operator=(const T& f)           { if (value == f)       return value; value = f;       pRealValue.markDirty(); onChanged(); return value; }
    virtual QJS_Prop<T>& operator=(const QJS_Prop<T>& f) { if (value == f.value) return *this; value = f.value; pRealValue.markDirty(); onChanged(); return *this; }


    QJS_Prop<T> &operator++() { value++; return *this; }
    QJS_Prop<T> &operator--() { value--; return *this; }

    virtual bool operator==(const T &right) const { return value == right; }
    virtual bool operator!=(const T &right) const { return !(value == right); }

    template<typename Y> void operator<<(const Y &another) { value << another; }
    template<typename Y> void operator>>(const Y &another) { value >> another; }
    template<typename V> T operator+=(const V &v) { return value += v; }
    template<typename V> T operator-=(const V &v) { return value -= v; }
    template<typename V> T operator*=(const V &v) { return value *= v; }
    template<typename V> T operator/=(const V &v) { return value /= v; }
    template<typename V> T operator&=(const V &v) { return value &= v; }
    template<typename V> T operator%=(const V &v) { return value %= v; }

    // JSON Serialization and Deserialization
    QJsonValue toJson() const { return JsonStructHelper::Serialize(value); }
    void loadJson(const QJsonValue &val) { JsonStructHelper::Deserialize(value, val); }
    // clang-format on

  private:
    T value;
    const T defaultValue;
    QProperty<T> pRealValue{ [this]() { return value; } };
    std::function<void(void)> onChanged;

  public:
    typedef T content_type;
    QJS_Prop(std::function<void(void)> callback, const T &val) : value(val), defaultValue(val), onChanged(callback){};
    virtual ~QJS_Prop() = default;

    bool isDefault() const
    {
        return value == defaultValue;
    }

    QPropertyChangeHandler<std::function<void()>> RBindTo(QObject *target, const char *target_prop)
    {
        target->setProperty(target_prop, pRealValue.value());
        return pRealValue.onValueChanged(std::function{ [=]() { target->setProperty(target_prop, pRealValue.value()); } });
    }

    template<typename TSender, typename Func>
    inline void WBindTo(const TSender *target, const char *target_prop, Func target_slot)
    {
        QObject::connect(target, target_slot, [=]() { *this = ((QObject *) target)->property(target_prop).value<T>(); });
    }
};

#define QJS_PROP(TYPE, NAME, ...) _QJS_PROP_IMPL(TYPE, NAME, TYPE{}, __VA_ARGS__)
#define QJS_PROP_D(TYPE, NAME, DEFAULT, ...) _QJS_PROP_IMPL(TYPE, NAME, DEFAULT, __VA_ARGS__)
#define QJS_CONSTRUCTOR(CLASS, ...) _QJS_CONSTRUCTOR_IMPL(CLASS, __VA_ARGS__)

#define QJS_FUNCTION(...)                                                                                                                            \
    QJS_FUNC_JSON(__VA_ARGS__);                                                                                                                      \
    QJS_FUNC_COMPARE(__VA_ARGS__);                                                                                                                   \
    QJS_FUNC_COPY(__VA_ARGS__);

#define QJS_RBINDING(sprop, target, tprop) property_bindings.push_back(sprop.RBindTo(target, tprop));
#define QJS_WBINDING(sprop, target, tprop, tslot) sprop.WBindTo(target, tprop, tslot);

#define QJS_RWBINDING(source_prop, target, target_prop, target_slot)                                                                                 \
    QJS_RBINDING(source_prop, target, target_prop);                                                                                                  \
    QJS_WBINDING(source_prop, target, target_prop, target_slot);

#define QJS_BINDING_CLEAR property_bindings.clear();
#define QJS_BINDING_HELPERS std::list<QPropertyChangeHandler<std::function<void()>>> property_bindings;
