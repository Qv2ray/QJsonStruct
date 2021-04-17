#pragma once

#include "macroexpansion.hpp"

// ============================================================================================
#define _QJS_COMPARE_F(...) FOR_EACH_2(__COMPARE_F, __VA_ARGS__)
#define _QJS_COMPARE_B(...) FOR_EACH_2(__COMPARE_B, __VA_ARGS__)
#define _QJS_COMPARE_BF(option) _QJS_COMPARE_##option

#define __COMPARE_F(name) (this->JS_F(name) == ___another___instance__.JS_F(name)) &&
#define __COMPARE_B(base) ((base) * this == (base) ___another___instance__) &&

#define QJS_FUNC_COMP(CLASS, ...)                                                                                                                    \
  public:                                                                                                                                            \
    bool operator==(const CLASS &___another___instance__) const                                                                                      \
    {                                                                                                                                                \
        QJsonObject ___json_object_;                                                                                                                 \
        return FOR_EACH(_QJS_COMPARE_BF, __VA_ARGS__) true;                                                                                          \
    }                                                                                                                                                \
                                                                                                                                                     \
    bool operator!=(const CLASS &_another) const                                                                                                     \
    {                                                                                                                                                \
        return !(*this == _another);                                                                                                                 \
    }

// ============================================================================================
#define QJS_FUNC_COPY(CLASS, ...)                                                                                                                    \
  public:                                                                                                                                            \
    CLASS(const CLASS &another)                                                                                                                      \
    {                                                                                                                                                \
        *this = another;                                                                                                                             \
    }                                                                                                                                                \
    CLASS &operator=(const CLASS &___another___instance__)                                                                                           \
    {                                                                                                                                                \
        FOR_EACH(_QJS_COPY_BF, __VA_ARGS__);                                                                                                         \
        return *this;                                                                                                                                \
    }
#define _QJS_COPY_B(...) FOR_EACH_2(__COPY_B, __VA_ARGS__)
#define _QJS_COPY_F(...) FOR_EACH_2(__COPY_F, __VA_ARGS__)
#define _QJS_COPY_BF(option) _QJS_COPY_##option

#define __COPY_B(base) base::operator=(___another___instance__);
#define __COPY_F(name) this->JS_F(name) = ___another___instance__.JS_F(name);

// ============================================================================================
