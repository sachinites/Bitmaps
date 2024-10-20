#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include "bitmap.h"

void bitmap_init(bitmap_t *bitmap, uint16_t size) {

    assert(!(size % 32));
    if (bitmap->bits) free(bitmap->bits);
    bitmap->bits = (uint32_t *)calloc(0, (size/8) * sizeof(uint8_t));
    bitmap->tsize = size;
    bitmap->next = 0;
}

void bitmap_free_internal(bitmap_t *bitmap) {
    free(bitmap->bits);
}

void bitmap_free(bitmap_t *bitmap) {
   bitmap_free_internal(bitmap);
   free(bitmap);
}

void bitmap_reset(bitmap_t *bitmap) {
    bitmap->next = 0;
    memset(bitmap->bits, 0, bitmap->tsize / 8);
}

bool bitmap_at(bitmap_t *bitmap, uint16_t index) {

    uint16_t n_blocks = index / 32;
    uint8_t bit_pos = index % 32;
    uint32_t *ptr = (uint32_t *)bitmap->bits + n_blocks;
    return htonl(*ptr) & (1 << (32 - bit_pos - 1));   
}

/* Endianess independent */
void
bitmap_set_bit_at(bitmap_t *bitmap, uint16_t index) {

    uint16_t n_blocks = index / 8;
    uint8_t bit_pos = index % 8;
    uint8_t *ptr = (uint8_t *)bitmap->bits + n_blocks;
    *ptr |=  (1 << (8 - bit_pos - 1));   
}

/* Endianess independent */
void
bitmap_unset_bit_at(bitmap_t *bitmap, uint16_t index) {

    uint16_t n_blocks = index / 8;
    uint8_t bit_pos = index % 8;
    uint8_t *ptr = (uint8_t *)bitmap->bits + n_blocks;
    *ptr &=  (~(1 << (8 - bit_pos - 1)));   
}

char *
bitmap_print(bitmap_t *bitmap) {

    uint16_t index;

    static char obuff[512];
    memset(obuff, 0, sizeof (obuff));

    assert (sizeof (obuff) > bitmap->tsize);
    int rc = 0;

    for (index = 0; index < bitmap->tsize; index++) {

        if (index && index % 8 == 0) {
            rc += sprintf (obuff + rc, " ");
        }

        rc += sprintf (obuff + rc, "%d", 
               bitmap_at(bitmap, index) ? 1 : 0);

    }

    return obuff;
}

