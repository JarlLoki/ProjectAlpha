#pragma once
#include <assert.h>

#ifdef _DEBUG

//#define PA_ASSERT(...) std::assert(__VA_ARGS__)
#define PA_ASSERT(...) 

#else

#define PA_ASSERT(...)

#endif


