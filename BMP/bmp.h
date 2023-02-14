#pragma once
#include "BMP/errors.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// TODO: define struct that is BMP header
// then replace this to be a struct that contains a header and data pointer
// http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
typedef struct BMP_ {
  uint8_t header[54];
  uint32_t width;
  uint32_t height;
  uint32_t size;
  uint8_t *data;
} BMP;

// Creates a new BMP object but it is not ready to use by default
int BMP_init(BMP **bmp);

// Provide referance to pointer of BMP image object in heap
// and a path.
int BMP_load_from_path(BMP **img, const char *path);

// Write Data in BMP object to specified path
int BMP_write_to_path(BMP *img, const char *path);

//
int BMP_get_pixel(BMP *img, int x, int y, int32_t pixel);

void BMP_fexplain_err(FILE *stream, int err);

