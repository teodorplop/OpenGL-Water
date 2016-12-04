#pragma once

#include<GL\glew.h>
#include<GL\freeglut.h>
#include<FreeImage.h>

class ImageUtils {
public:
	static BYTE* Load_Image(const char* filename, GLsizei* width, GLsizei* height);
	static FIBITMAP* Load_Image(const char* filename);
	static void Unload_Image(FIBITMAP* image);
};