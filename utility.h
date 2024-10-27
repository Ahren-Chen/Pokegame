// types_and_macros.h
#ifndef TYPES_AND_MACROS_H
#define TYPES_AND_MACROS_H

// Type definitions
typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;

// Macros
#define global_variable static
#define internal static

// Inline function definition
inline int clamp(int min, int val, int max) {
    if (val < min) {
        return min;
    }
    else if (val > max) {
        return max;
    }
    else {
        return val;
    }
}

#endif // TYPES_AND_MACROS_H
