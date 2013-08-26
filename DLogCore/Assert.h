#pragma once

#ifdef _DEBUG

void __ASSERT__(bool expr_value, const char* expression, int line, const char* func_name);

#define ASSERT(expr) __ASSERT__((expr), #expr, __LINE__, __PRETTY_FUNCTION__)
#define DEBUG_EXPR(expr) expr

#else

#define ASSERT(expr)
#define DEBUG_EXPR(expr)

#endif
