#include "BMP/bmp.h"
#include "BMP/errors.h"
#include <stddef.h>
// reading operations
#include <stdio.h>
// writing operations
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int BMPSIZE = sizeof(BMP);
int BMP_init(BMP **bmp) {

  *bmp = (BMP *)malloc(BMPSIZE);
  if (*bmp == NULL) {
    return BMP_MEM_ALLOC_FAIL;
  }
  memset(*bmp, 0, BMPSIZE);
  return BMP_SUCCESS;
}

int BMP_load_from_path(BMP **img, const char *path) {
  uint8_t header[54]; // Each BMP file begins by a 54-bytes header
  uint32_t dataPos;   // Position in the file where the actual data begins
  uint32_t width, height;
  uint32_t imageSize; // = width*height*3
  // Actual RGB data
  uint8_t *data;

  FILE *file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "File Could not be opened: %s\n", path);
    return BMP_GENERIC_FAIL;
  }

  if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
    fprintf(stderr, "Not a correct BMP file: %s\n", path);
    return BMP_INCORRECT_FORMAT;
  }

  if (header[0] != 'B' || header[1] != 'M') {
    fprintf(stderr, "Not a correct BMP file: %s\n", path);
    return 0;
  }

  dataPos = *(int *)&(header[0x0A]);
  width = *(int *)&(header[0x12]);
  height = *(int *)&(header[0x16]);
  imageSize = *(int *)&(header[0x22]);

  // Some BMP files are misformatted, guess missing information
  if (imageSize == 0)
    imageSize = width * height *
                3; // 3 : one byte for each Red, Green and Blue component
  if (dataPos == 0)
    dataPos = 54; // The BMP header is done that way

  data = (uint8_t *)malloc(imageSize);

  // Read the actual data from the file into the buffer
  if (0 == fread(data, 1, imageSize, file)) {
    fprintf(stderr, "BMP Data Bytes Could Not Be Read\n");
    fclose(file);
    return BMP_INCORRECT_FORMAT;
  }

  // Everything is in memory now, the file can be closed
  fclose(file);
  /// BMP does not store Red->Green->Blue but Blue->Green->Red, so we have to
  /// tell it to OpenGL. example:
  ///  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR,
  ///  GL_UNSIGNED_BYTE, data);

  memcpy((*img)->header, header, 54);
  (*img)->width = width;
  (*img)->height = height;
  (*img)->size = imageSize;
  (*img)->data = data;
  return BMP_SUCCESS;
}

int BMP_write_to_path(BMP *img, const char *path) {
  printf("Image Pointer: %p, Image Path: %s\n", (void *)img, path);
  uint8_t header[54];
  memcpy(header, img->header, 54);
  header[0] = 'B';
  header[1] = 'M';
  header[10] = 54;
  header[18] = img->width;
  header[22] = img->height;
  header[34] = img->size;
  FILE *target = fopen(path, "w");
  if (target == NULL) {
    fprintf(stderr, "New File Could Not Be Opended");
    return BMP_GENERIC_FAIL;
  }
  // ize_t fwrite (const void *data, size_t size, size_t count, FILE *stream)
  int write_result = fwrite(header, 1, 54, target);
  if (write_result != 54) {
    fprintf(stderr, "File Header Could not be written: %s\nWrite Result: %d\n",
            path, write_result);
    return BMP_GENERIC_FAIL;
  }

  int data_result = fwrite(img->data, 1, img->size, target);
  if ((uint32_t)data_result != img->size) {
    fprintf(stderr, "BMP Image Data could not be written.\n");
    return BMP_GENERIC_FAIL;
  }
  fclose(target);
  return BMP_SUCCESS;
}

void BMP_fexplain_err(FILE *stream, int err) {
  switch (err) {
  case BMP_SUCCESS:
    fprintf(stream, "Everything is fine, no worries\n");
    break;
  case BMP_GENERIC_FAIL:
    fprintf(stream, "Denotes that something has gone wrong\n");
    break;
  case BMP_MEM_ALLOC_FAIL:
    fprintf(stream, "Failed to Allocated Memory, Check errno\n");
    break;
  case BMP_INCORRECT_FORMAT:
    fprintf(stream, "Denotes that BMP file is formatted incorrectly\n");
    break;
  default:
    fprintf(stream, "Unknown Error?\n");
  }
}

int BMP_destroy(BMP *img){
  free(img->data);
  free(img);
  return BMP_SUCCESS;
}
