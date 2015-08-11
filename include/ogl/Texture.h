#ifndef TEXTURE_H
#define TEXTURE_H

#include <IL/il.h>
#include <gl/glew.h>
#include <iostream>

#pragma comment(lib, "DevIL.lib")

GLuint loadTexture(const  char* theFileName);


#endif