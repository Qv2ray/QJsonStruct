#pragma once
#include "CompareMacros.hpp"
#include "ConstructorMacros.hpp"
#include "JsonConvertMacros.hpp"
#include "QJsonStructBase.hpp"
#include "macroexpansion.hpp"

#define _S_PROPERTY_IMPL(TYPE, NAME, DEFAULT, REQ)                                                                                                   \
  private:                                                                                                                                           \
    TYPE QJSONSTRUCT_FIELD(NAME) = (DEFAULT);                                                                                                        \
    const TYPE __default__##NAME = (DEFAULT);                                                                                                        \
                                                                                                                                                     \
  public:                                                                                                                                            \
    /* set function with signals emiting */                                                                                                          \
    void set_##NAME(const TYPE _new)                                                                                                                 \
    {                                                                                                                                                \
        this->QJSONSTRUCT_FIELD(NAME) = _new;                                                                                                        \
        emit on_##NAME##_changed(_new);                                                                                                              \
    }                                                                                                                                                \
    /* const get function */                                                                                                                         \
    const TYPE &NAME() const                                                                                                                         \
    {                                                                                                                                                \
        return QJSONSTRUCT_FIELD(NAME);                                                                                                              \
    }                                                                                                                                                \
    /* non const get function */                                                                                                                     \
    TYPE &NAME()                                                                                                                                     \
    {                                                                                                                                                \
        return QJSONSTRUCT_FIELD(NAME);                                                                                                              \
    }                                                                                                                                                \
    /* reset function */                                                                                                                             \
    void reset_##NAME()                                                                                                                              \
    {                                                                                                                                                \
        set_##NAME(__default__##NAME);                                                                                                               \
    }                                                                                                                                                \
    /* on value changed signal */                                                                                                                    \
    Q_SIGNAL void on_##NAME##_changed(const TYPE &);                                                                                                 \
    Q_PROPERTY(TYPE NAME MEMBER QJSONSTRUCT_FIELD(NAME) NOTIFY on_##NAME##_changed RESET reset_##NAME REQ)

#define _SELECT_TOP_FUNC2(type, bases, fields, func) JS_##func(type, bases, fields)

// ========================================================================================================
//
// QJsonStruct Public APIS
//
// ========================================================================================================

#define JS_PROP_M(TYPE, NAME, DEFAULT) _S_PROPERTY_IMPL(TYPE, NAME, DEFAULT, REQUIRED)
#define JS_PROP_O(TYPE, NAME, DEFAULT) _S_PROPERTY_IMPL(TYPE, NAME, DEFAULT, )
#define JS_REGISTER(CLASS, BASES, FIELDS, ...)                                                                                                       \
    JS_MACRO_ARGUMENT_NO_WARN                                                                                                                        \
    FOREACH_CALL_FUNC_WITH3(_SELECT_TOP_FUNC2, CLASS, BASES, FIELDS, __VA_ARGS__)                                                                    \
    JS_MACRO_ARGUMENT_RESTORE_WARN
