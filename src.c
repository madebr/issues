#include <stddef.h>
#include <stdint.h>

typedef int64_t  br_int_64;
typedef uint64_t br_uint_64;
typedef int32_t  br_int_32;
typedef uint32_t br_uint_32;
typedef int16_t  br_int_16;
typedef uint16_t br_uint_16;
typedef int8_t  br_int_8;
typedef uint8_t br_uint_8;
typedef float br_float;
typedef int br_boolean;
#define BR_TRUE		1
#define BR_FALSE	0

typedef br_int_32 br_fixed_ls;
typedef br_uint_16 br_fixed_luf;

typedef br_fixed_luf br_angle;

typedef br_float br_scalar;
typedef br_uint_32 br_colour;

typedef struct br_matrix23 {
    br_scalar m[3][2];
} br_matrix23;
typedef struct br_matrix34 {
    br_scalar m[4][3];
} br_matrix34;
typedef struct br_matrix4_f {
    br_float m[4][4];
} br_matrix4_f;


typedef enum br_token {
    BR_NULL_TOKEN = 0,
    BRT_NONE = 1,
    BRT_BOOLEAN = 2,
    BRT_POINTER = 3,
    BRT_TOKEN = 4,
    BRT_INT_8 = 5,
    BRT_UINT_8 = 6,
    BRT_INT_16 = 7,
    BRT_UINT_16 = 8,
    BRT_INT_32 = 9,
    BRT_UINT_32 = 10,
    BRT_FIXED = 11,
    BRT_FLOAT = 12,
    BRT_ANGLE = 13,
    BRT_COLOUR_RGB = 14,
    BRT_OBJECT = 15,
    BRT_VECTOR2_INTEGER = 16,
    BRT_VECTOR3_INTEGER = 17,
    BRT_VECTOR4_INTEGER = 18,
    BRT_VECTOR2_FIXED = 19,
    BRT_VECTOR3_FIXED = 20,
    BRT_VECTOR4_FIXED = 21,
    BRT_VECTOR2_FLOAT = 22,
    BRT_VECTOR3_FLOAT = 23,
    BRT_VECTOR4_FLOAT = 24,
    BRT_MATRIX23_FIXED = 25,
    BRT_MATRIX34_FIXED = 26,
    BRT_MATRIX4_FIXED = 27,
    BRT_MATRIX23_FLOAT = 28,
    BRT_MATRIX34_FLOAT = 29,
    BRT_MATRIX4_FLOAT = 30,
    BRT_STRING = 31,
    BRT_ALTERNATIVE_TO_DEFAULT_B   =      150,
} br_token;

typedef union br_value_tag {
    void                  *p;
    br_boolean		b;
    br_token		t;
    br_int_8		i8;
    br_uint_8		u8;
    br_int_16		i16;
    br_uint_16		u16;
    br_int_32		i32;
    br_uint_32		u32;
    br_fixed_ls		x;
    br_float		f;
    br_scalar		s;
    br_angle		a;
    br_colour		rgb;
    struct br_object *o;
    void			*h;
    br_matrix34 	*m34;
    br_matrix23		*m23;
    char *			str;
    char *			cstr;
    struct br_object **ol;
    br_token		*tl;
    void *			*pl;
    br_int_64       i64;
    br_uint_64      u64;
    struct br_token_value *tvl;
} br_value ;


typedef struct br_token_value {
    br_token t ;
    br_value v ;
} br_token_value;

int main(int argc, char *argv[]) {
    br_token_value is_alternative[] = {
            { BRT_ALTERNATIVE_TO_DEFAULT_B, (br_value) { .t = BR_TRUE } },
            { BR_NULL_TOKEN , (br_value) { .p = NULL }}
    };
    return 0;
}
