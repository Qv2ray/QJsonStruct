#pragma once

#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2
#define CONCATENATE(x, y) x##y

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_01, _02, _03, _04, _05, _06, _07, _08, _09, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define FOR_EACH_RSEQ_N() 16, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00

#define EXPAND(...) __VA_ARGS__

// Bad hack ==========================================================================================================================

#define FOR_EACH_WITH1_01(what, with, x, ...) what(with, x)
#define FOR_EACH_WITH1_02(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_01(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_03(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_02(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_04(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_03(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_05(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_04(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_06(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_05(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_07(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_06(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_08(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_07(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_09(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_08(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_10(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_09(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_11(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_10(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_12(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_11(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_13(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_12(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_14(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_13(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_15(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_14(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_16(what, with, x, ...) what(with, x) EXPAND(FOR_EACH_WITH1_15(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1_(N, what, with, ...) EXPAND(CONCATENATE(FOR_EACH_WITH1_, N)(what, with, __VA_ARGS__))
#define FOR_EACH_WITH1(what, with, ...) FOR_EACH_WITH1_(FOR_EACH_NARG(__VA_ARGS__), what, with, __VA_ARGS__)
#define FOREACH_CALL_FUNC_WITH(what, with, ...) FOR_EACH_WITH1(what, with, __VA_ARGS__)

// Bad hack ==========================================================================================================================

#define FOR_EACH_WITH2_01(what, w1, w2, x) what(w1, w2, x)
#define FOR_EACH_WITH2_02(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_01(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_03(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_02(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_04(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_03(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_05(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_04(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_06(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_05(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_07(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_06(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_08(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_07(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_09(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_08(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_10(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_09(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_11(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_10(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_12(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_11(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_13(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_12(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_14(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_13(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_15(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_14(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_16(what, w1, w2, x, ...) what(w1, w2, x) EXPAND(FOR_EACH_WITH2_15(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2_(N, what, w1, w2, ...) EXPAND(CONCATENATE(FOR_EACH_WITH2_, N)(what, w1, w2, __VA_ARGS__))
#define FOR_EACH_WITH2(what, w1, w2, ...) FOR_EACH_WITH2_(FOR_EACH_NARG(__VA_ARGS__), what, w1, w2, __VA_ARGS__)
#define FOREACH_CALL_FUNC_WITH2(what, w1, w2, ...) FOR_EACH_WITH2(what, w1, w2, __VA_ARGS__)

// Bad hack ==========================================================================================================================

#define FOR_EACH_WITH3_01(what, w1, w2, w3, x) what(w1, w2, w3, x)
#define FOR_EACH_WITH3_02(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_01(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_03(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_02(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_04(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_03(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_05(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_04(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_06(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_05(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_07(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_06(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_08(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_07(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_09(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_08(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_10(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_09(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_11(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_10(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_12(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_11(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_13(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_12(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_14(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_13(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_15(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_14(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_16(what, w1, w2, w3, x, ...) what(w1, w2, w3, x) EXPAND(FOR_EACH_WITH3_15(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3_(N, what, w1, w2, w3, ...) EXPAND(CONCATENATE(FOR_EACH_WITH3_, N)(what, w1, w2, w3, __VA_ARGS__))
#define FOR_EACH_WITH3(what, w1, w2, w3, ...) FOR_EACH_WITH3_(FOR_EACH_NARG(__VA_ARGS__), what, w1, w2, w3, __VA_ARGS__)
#define FOREACH_CALL_FUNC_WITH3(what, w1, w2, w3, ...) FOR_EACH_WITH3(what, w1, w2, w3, __VA_ARGS__)
// Bad hack ==========================================================================================================================

#define FOR_EACH_00(...)
#define FOR_EACH_01(what, x, ...) what(x)
#define FOR_EACH_02(what, x, ...) what(x) EXPAND(FOR_EACH_01(what, __VA_ARGS__))
#define FOR_EACH_03(what, x, ...) what(x) EXPAND(FOR_EACH_02(what, __VA_ARGS__))
#define FOR_EACH_04(what, x, ...) what(x) EXPAND(FOR_EACH_03(what, __VA_ARGS__))
#define FOR_EACH_05(what, x, ...) what(x) EXPAND(FOR_EACH_04(what, __VA_ARGS__))
#define FOR_EACH_06(what, x, ...) what(x) EXPAND(FOR_EACH_05(what, __VA_ARGS__))
#define FOR_EACH_07(what, x, ...) what(x) EXPAND(FOR_EACH_06(what, __VA_ARGS__))
#define FOR_EACH_08(what, x, ...) what(x) EXPAND(FOR_EACH_07(what, __VA_ARGS__))
#define FOR_EACH_09(what, x, ...) what(x) EXPAND(FOR_EACH_08(what, __VA_ARGS__))
#define FOR_EACH_10(what, x, ...) what(x) EXPAND(FOR_EACH_09(what, __VA_ARGS__))
#define FOR_EACH_11(what, x, ...) what(x) EXPAND(FOR_EACH_10(what, __VA_ARGS__))
#define FOR_EACH_12(what, x, ...) what(x) EXPAND(FOR_EACH_11(what, __VA_ARGS__))
#define FOR_EACH_13(what, x, ...) what(x) EXPAND(FOR_EACH_12(what, __VA_ARGS__))
#define FOR_EACH_14(what, x, ...) what(x) EXPAND(FOR_EACH_13(what, __VA_ARGS__))
#define FOR_EACH_15(what, x, ...) what(x) EXPAND(FOR_EACH_14(what, __VA_ARGS__))
#define FOR_EACH_16(what, x, ...) what(x) EXPAND(FOR_EACH_15(what, __VA_ARGS__))

#define FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)
#define FOREACH_CALL_FUNC(what, ...) FOR_EACH(what, __VA_ARGS__)

// Bad hack ==========================================================================================================================
#define _2X_FOR_EACH_01(what, x, ...) what(x)
#define _2X_FOR_EACH_02(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_01(what, __VA_ARGS__))
#define _2X_FOR_EACH_03(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_02(what, __VA_ARGS__))
#define _2X_FOR_EACH_04(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_03(what, __VA_ARGS__))
#define _2X_FOR_EACH_05(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_04(what, __VA_ARGS__))
#define _2X_FOR_EACH_06(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_05(what, __VA_ARGS__))
#define _2X_FOR_EACH_07(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_06(what, __VA_ARGS__))
#define _2X_FOR_EACH_08(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_07(what, __VA_ARGS__))
#define _2X_FOR_EACH_09(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_08(what, __VA_ARGS__))
#define _2X_FOR_EACH_10(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_09(what, __VA_ARGS__))
#define _2X_FOR_EACH_11(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_10(what, __VA_ARGS__))
#define _2X_FOR_EACH_12(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_11(what, __VA_ARGS__))
#define _2X_FOR_EACH_13(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_12(what, __VA_ARGS__))
#define _2X_FOR_EACH_14(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_13(what, __VA_ARGS__))
#define _2X_FOR_EACH_15(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_14(what, __VA_ARGS__))
#define _2X_FOR_EACH_16(what, x, ...) what(x) EXPAND(_2X_FOR_EACH_15(what, __VA_ARGS__))
#define _2X_FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(_2X_FOR_EACH_, N)(what, __VA_ARGS__))
#define _2X_FOR_EACH(what, ...) _2X_FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)
#define FOREACH_CALL_FUNC_2(what, ...) _2X_FOR_EACH(what, __VA_ARGS__)

// Bad hack ==========================================================================================================================
#define _3X_FOR_EACH_01(what, x, ...) what(x)
#define _3X_FOR_EACH_02(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_01(what, __VA_ARGS__))
#define _3X_FOR_EACH_03(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_02(what, __VA_ARGS__))
#define _3X_FOR_EACH_04(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_03(what, __VA_ARGS__))
#define _3X_FOR_EACH_05(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_04(what, __VA_ARGS__))
#define _3X_FOR_EACH_06(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_05(what, __VA_ARGS__))
#define _3X_FOR_EACH_07(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_06(what, __VA_ARGS__))
#define _3X_FOR_EACH_08(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_07(what, __VA_ARGS__))
#define _3X_FOR_EACH_09(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_08(what, __VA_ARGS__))
#define _3X_FOR_EACH_10(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_09(what, __VA_ARGS__))
#define _3X_FOR_EACH_11(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_10(what, __VA_ARGS__))
#define _3X_FOR_EACH_12(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_11(what, __VA_ARGS__))
#define _3X_FOR_EACH_13(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_12(what, __VA_ARGS__))
#define _3X_FOR_EACH_14(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_13(what, __VA_ARGS__))
#define _3X_FOR_EACH_15(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_14(what, __VA_ARGS__))
#define _3X_FOR_EACH_16(what, x, ...) what(x) EXPAND(_3X_FOR_EACH_15(what, __VA_ARGS__))
#define _3X_FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(_3X_FOR_EACH_, N)(what, __VA_ARGS__))
#define _3X_FOR_EACH(what, ...) _3X_FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)
#define FOREACH_CALL_FUNC_3(what, ...) _3X_FOR_EACH(what, __VA_ARGS__)
