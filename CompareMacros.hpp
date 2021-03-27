#pragma once

#include "macroexpansion.hpp"

#define _COMPARE_F_IMPL(x) (this->_##x == ___another___instance__._##x) &&
#define _COMPARE_B_IMPL(b) ((b) * this == (b) _another) &&

#define JS_COMPARE_F(CLASS, bs, fs)                                                                                                                  \
    bool operator==(const CLASS &___another___instance__) const                                                                                      \
    {                                                                                                                                                \
        return FOR_EACH(_COMPARE_F_IMPL, ESC fs) true;                                                                                               \
    }                                                                                                                                                \
    bool operator!=(const CLASS &_another) const                                                                                                     \
    {                                                                                                                                                \
        return !(*this == _another);                                                                                                                 \
    }

#define JS_COMPARE_FB(CLASS, bs, fs)                                                                                                                 \
    bool operator==(const CLASS &___another___instance__) const                                                                                      \
    {                                                                                                                                                \
        return FOR_EACH(_COMPARE_B_IMPL, PASS_PARAMETERS(bs)) FOR_EACH(_COMPARE_F_IMPL, ESC fs) true;                                                \
    }                                                                                                                                                \
    bool operator!=(const CLASS &_another) const                                                                                                     \
    {                                                                                                                                                \
        return !(*this == _another);                                                                                                                 \
    }
