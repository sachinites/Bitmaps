#ifndef __BITMAP__
#define __BITMAP__

#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef enum {
	ZERO,
	ONE,
	DONT_CARE,
	BIT_TYPE_MAX
} bit_type_t;

typedef struct bitmap_ {

    uint32_t *bits;
    uint16_t tsize;
    uint16_t next;
} bitmap_t;

void bitmap_init(bitmap_t *bitmap, uint16_t size) ;
void bitmap_free_internal(bitmap_t *bitmap);
void bitmap_free(bitmap_t *bitmap);
void bitmap_reset(bitmap_t *bitmap);
bool bitmap_at(bitmap_t *bitmap, uint16_t index);
void bitmap_set_bit_at(bitmap_t *bitmap, uint16_t index) ;
void bitmap_unset_bit_at(bitmap_t *bitmap, uint16_t index) ;

char *bitmap_print(bitmap_t *bitmap); 

#endif 