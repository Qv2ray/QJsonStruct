#pragma once

#define JS_F(x) x

#define JS_MACRO_ARGUMENT_NO_WARN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")
#define JS_MACRO_ARGUMENT_RESTORE_WARN _Pragma("clang diagnostic pop")
