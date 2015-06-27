#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#define DIGESTBYTES 64

#define R 10
typedef signed char s8;
typedef unsigned char u8;

#if UINT_MAX >= 4294967295UL

typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;

#define ONE32   0xffffffffU

#else

typedef signed int s16;
typedef signed long s32;
typedef unsigned int u16;
typedef unsigned long u32;

#define ONE32   0xffffffffUL

#endif

#define ONE8    0xffU
#define ONE16   0xffffU

#define T8(x)   ((x) & ONE8)
#define T16(x)  ((x) & ONE16)
#define T32(x)  ((x) & ONE32)

#ifdef _MSC_VER
typedef unsigned __int64 u64;
typedef signed __int64 s64;
#define ONE64   0xffffffffffffffffi64
#else
typedef unsigned long long u64;
typedef signed long long s64;
#define ONE64   0xffffffffffffffffULL
#endif
#define T64(x)  ((x) & ONE64)
#define ROTR64(v, n)   (((v) >> (n)) | T64((v) << (64 - (n))))

typedef unsigned __int64 u64;

typedef struct TheWStruct {
    u8  _bitLength[32]; /// number of hashed bits
    u8  _buffer[64]; /// data to hash
    int _bufferBits; /// current number of bits
    int _bufferPos; /// curren byte slot on the buffer
    u64 _hash[8]; /// hashing state
} TheWStruct;
#endif // DEFINES_H_INCLUDED
