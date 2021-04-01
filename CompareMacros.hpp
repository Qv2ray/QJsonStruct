#pragma once

#include "macroexpansion.hpp"

#define QJS_FUNC_COMPARE(...)                                                                                                                        \
  public:                                                                                                                                            \
    bool operator==(const this_type_t &___another___instance__) const                                                                                \
    {                                                                                                                                                \
        QJsonObject ___json_object_;                                                                                                                 \
        return FOR_EACH(_QJS_COMPARE_BF, __VA_ARGS__) true;                                                                                          \
    }                                                                                                                                                \
    bool operator!=(const this_type_t &_another) const                                                                                               \
    {                                                                                                                                                \
        return !(*this == _another);                                                                                                                 \
    }

// ============================================================================================
#define _QJS_COMPARE_F(...) FOR_EACH_2(__COMPARE_F, __VA_ARGS__)
#define _QJS_COMPARE_B(...) FOR_EACH_2(__COMPARE_B, __VA_ARGS__)
#define _QJS_COMPARE_BF(option) _QJS_COMPARE_##option

#define __COMPARE_F(name) (this->JS_F(name) == ___another___instance__.JS_F(name)) &&
#define __COMPARE_B(base) ((base) * this == (base) ___another___instance__) &&
