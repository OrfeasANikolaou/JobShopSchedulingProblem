/* 
 * https://google.github.io/styleguide/cppguide.html#The__define_Guard
 * All header files should have #define guards to prevent multiple inclusion. 
 * The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_. 
 */
#ifndef JSSP_HEADERS_BETTER_DATATYPES_H
#define JSSP_HEADERS_BETTER_DATATYPES_H
#include <stdint.h>
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8; // signed char NEVER USE THIS
typedef uint8_t u8; // unsigned char
typedef float f32;
typedef double f64;
typedef long double f128;
typedef wchar_t fat_char;
#endif
