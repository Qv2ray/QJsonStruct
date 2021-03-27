#pragma once

#include "QJsonStructBase.hpp"
#include "macroexpansion.hpp"

#define _ASSIGN(x) this->set_##x(another.x());
#define JS_CCTOR(CLASS, b, fs)                                                                                                                       \
    CLASS(const CLASS &another)                                                                                                                      \
    {                                                                                                                                                \
        for (int i = 1; i < this->metaObject()->propertyCount(); i++)                                                                                \
        {                                                                                                                                            \
            const auto prop = metaObject()->property(i);                                                                                             \
            if (prop.isConstant())                                                                                                                   \
                continue;                                                                                                                            \
            const auto name = prop.name();                                                                                                           \
            this->setProperty(name, another.property(name));                                                                                         \
        }                                                                                                                                            \
    };                                                                                                                                               \
    void operator=(const CLASS &another)                                                                                                             \
    {                                                                                                                                                \
        FOR_EACH(_ASSIGN, ESC fs)                                                                                                                    \
    }

#define JS_DCTOR(CLASS, ...) CLASS(){};
