#pragma once

#define ESC(...) __VA_ARGS__

#define QJSONSTRUCT_FIELD(x) _##x

#define JS_MACRO_ARGUMENT_NO_WARN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")
#define JS_MACRO_ARGUMENT_RESTORE_WARN _Pragma("clang diagnostic pop")
