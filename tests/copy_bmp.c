#include "BMP/bmp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  puts("Hello World!");
  printf("Number of Args: %d\n", argc);
  char *path = argv[1];
  BMP *bmp;
  int init_status = BMP_init(&bmp);
  BMP_fexplain_err(stderr, init_status);
  int load_status = BMP_load_from_path(&bmp, path);
  BMP_fexplain_err(stderr, load_status);

  BMP_write_to_path(bmp, "images/output.bmp");

  BMP_destroy(bmp);

  return EXIT_SUCCESS;
}
