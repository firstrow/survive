#ifndef TYPES_H_
#define TYPES_H_

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#include <inttypes.h>
#include <stddef.h>

extern int DIAMOND_SIZE;
extern int tile_width;
extern int tile_height;
extern int camera_x;
extern int camera_y;
extern double SCALE_FACTOR;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float   f32;
typedef double  f64;
typedef size_t usize;

typedef struct {
    float x;
    float y;
} vec2;

#endif // TYPES_H_
