/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Images.cpp/h
 Desc: C-Style image loading and saving functions. Based on
 interfacing with stb_image from author Sean Barrett and his
 published code on http://nothings.org/
 
 Loads all of the following formats: (based on stb_images)
 
 JPEG baseline (no JPEG progressive)
 PNG 8-bit only
 
 TGA (not sure what subset, if a subset)
 BMP non-1bpp, non-RLE
 PSD (composited view only, no extra channels)
 
 GIF (*comp always reports as 4-channel)
 HDR (radiance rgbE format)
 PIC (Softimage PIC)
 
***************************************************************/

// Inclusion guard
#ifndef __G2IMAGES_H__
#define __G2IMAGES_H__

#include "stb_image.h"
#include <map>
#include <string>
#include "impl/glut.h"
#include <string.h>
// Image allocation structure
static const int __g2ImageFileNameLength = 512;
struct __g2Image
{
    // Name of file
    char FileName[__g2ImageFileNameLength];
    
    // Width, height
    int Width, Height;
    
    // Components (channel count)
    int Channels;
    
    // The OpenGL texture ID
    GLuint GlTextureID;
};

// Open a given image and copy it into the OpenGL image buffers;
// if the image has not yet been opened before, then a unique reference
// is made, otherwise a copy isn't made but the same reference is returned
// Return a negative value if unable to open file / image
GLuint g2LoadImage(const char* ImagePath, int* Width = NULL, int* Height = NULL, int* Channels = NULL, bool Wrap = false, bool GenerateMips = true);

// Open a given image and provide directly memory access to it; must
// be released using the "g2UnloadImageBuffer" function when done with
// the buffer. Sets the given buffer to NULL if unable to load image
void g2LoadImageBuffer(const char* ImagePath, unsigned char** OutBuffer, int* Width = NULL, int* Height = NULL, int* Channels = NULL);

// Release a buffer allocated by "g2LoadImageBuffer"
void g2UnloadImageBuffer(unsigned char* OutBuffer);

// End of inclusion guard
#endif
