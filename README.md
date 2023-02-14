# BMPGL

Library for use in OpenGL

```c
// Example

BMP *img
int init_status = BMP_init(&img);
int load_status = BMP_load_from_path(&img, path);
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, img->width, img->height, 0, GL_BGR, GL_UNSIGNED_BYTE, img->data)
```
