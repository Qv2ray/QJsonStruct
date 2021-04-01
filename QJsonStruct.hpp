#pragma once

#include "CompareMacros.hpp"
#include "JsonConvertMacros.hpp"

#include <QProperty>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #error "QJsonStruct does not support Qt version lesser than 6.0.0."
#endif

#define _QJS_PROP_OPTIONAL false
#define _QJS_PROP_REQUIRED true

// ========================================================================================================
//
// QJsonStruct Public APIS
//
// ========================================================================================================

#define QJS_PROP(TYPE, NAME, DEFAULT, EXTRA)                                                                                                         \
  private:                                                                                                                                           \
    TYPE JS_F(NAME) = (DEFAULT);                                                                                                                     \
    const TYPE __default__##NAME = (DEFAULT);                                                                                                        \
    constexpr static bool prop_##NAME##_required = _QJS_PROP_##EXTRA;                                                                                \
                                                                                                                                                     \
  public:                                                                                                                                            \
    QProperty<TYPE> p##NAME = QProperty<TYPE>([this]() { return _##NAME; });                                                                         \
    void set_##NAME(const TYPE _new)                                                                                                                 \
    {                                                                                                                                                \
        this->JS_F(NAME) = _new;                                                                                                                     \
        this->p##NAME.markDirty();                                                                                                                   \
    }                                                                                                                                                \
    std::add_const_t<TYPE> NAME() const                                                                                                              \
    {                                                                                                                                                \
        return JS_F(NAME);                                                                                                                           \
    }                                                                                                                                                \
    TYPE &NAME()                                                                                                                                     \
    {                                                                                                                                                \
        return JS_F(NAME);                                                                                                                           \
    }

#define QJS_CONSTRUCTOR(CLASS)                                                                                                                       \
    typedef CLASS this_type_t;                                                                                                                       \
                                                                                                                                                     \
  public:                                                                                                                                            \
    CLASS(){};                                                                                                                                       \
    CLASS(const this_type_t &another)                                                                                                                \
    {                                                                                                                                                \
        *this = another;                                                                                                                             \
    }                                                                                                                                                \
    void operator=(const this_type_t &another)                                                                                                       \
    {                                                                                                                                                \
        /* "Deep Copy" */                                                                                                                            \
        loadJson(another.toJson());                                                                                                                  \
    }

#define QJS_FUNCTION(...) JS_MACRO_ARGUMENT_NO_WARN QJS_FUNC_JSON(__VA_ARGS__) QJS_FUNC_COMPARE(__VA_ARGS__) JS_MACRO_ARGUMENT_RESTORE_WARN

#define QJS_RBINDING(source, source_prop, target, target_prop)                                                                                       \
    do                                                                                                                                               \
    {                                                                                                                                                \
        target->setProperty(#target_prop, source.p##source_prop.value());                                                                            \
        const auto lambda = [this]() { target->setProperty(#target_prop, source.p##source_prop.value()); };                                          \
        pch.push_back(source.p##source_prop.onValueChanged(std::function{ lambda }));                                                                \
    } while (false)

#define QJS_WBINDING(source, source_prop, target, target_prop, target_slot)                                                                          \
    do                                                                                                                                               \
    {                                                                                                                                                \
        connect(target, target_slot, [this]() {                                                                                                      \
            if (!x.tryLock())                                                                                                                        \
                return;                                                                                                                              \
            this->source.set_##source_prop(target->target_prop());                                                                                   \
            x.unlock();                                                                                                                              \
        });                                                                                                                                          \
    } while (false)

#define QJS_RWBINDING(source, source_prop, target, target_prop, target_slot)                                                                         \
    QJS_RBINDING(source, source_prop, target, target_prop);                                                                                          \
    QJS_WBINDING(source, source_prop, target, target_prop, target_slot);
