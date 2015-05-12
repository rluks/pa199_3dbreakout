#ifndef _PNG_TEXTURE
#define _PNG_TEXTURE

#include "../OpenGLIncludes.h"
#include <png.h>

GLuint png_texture_load(const char * file_name, int * width, int * height);

#endif