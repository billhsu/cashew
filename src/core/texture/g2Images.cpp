/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
***************************************************************/

#include "g2Images.h"
#include <iostream>

// Internal allocations of images
std::map<std::string, __g2Image> __g2ImageList;
typedef std::map<std::string, __g2Image>::iterator __g2ImagesListIt;

// Load any given image
GLuint g2LoadImage(const char* ImagePath, int* Width, int* Height, int* Channels, bool Wrap, bool GenerateMips)
{
    // Does the image already exist in the dictionary?
    __g2ImagesListIt Result = __g2ImageList.find(std::string(ImagePath));
    
    // If nothing is found...
    if(Result == __g2ImageList.end())
    {
        // Create a new image instance
        __g2Image Image;
        strcpy(Image.FileName, ImagePath);
        
        // Allocate image; fail out on error
        unsigned char* DataBuffer = stbi_load(ImagePath, &Image.Width, &Image.Height, &Image.Channels, 4);
        if(DataBuffer == NULL)
            return -1;
        
        //glEnable(GL_TEXTURE_2D);
        // Allocate an OpenGL texture
        glGenTextures(1, &Image.GlTextureID);
        glBindTexture(GL_TEXTURE_2D, Image.GlTextureID);
        std::cout<<ImagePath<<" ID: "<<Image.GlTextureID<<std::endl;

        // Generate mipmaps if desired
        if(GenerateMips)
        {
            // Build mip map
            gluBuild2DMipmaps(GL_TEXTURE_2D, (Image.Channels == 3) ? GL_RGB8 : GL_RGBA8, Image.Width, Image.Height, (Image.Channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, DataBuffer);
            
            // Linear (simple and smooth) interpolation
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        // Else, make very accurate sans blending
        else
        {
            // Build the image buffer
            glTexImage2D(GL_TEXTURE_2D, 0, (Image.Channels == 3) ? GL_RGB8 : GL_RGBA8, Image.Width, Image.Height, 0, (Image.Channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, DataBuffer);
            
            // Nearest-neighbor (i.e. no smoothing) interpolation
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        
        // Wrap texture around
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap ? GL_REPEAT : GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap ? GL_REPEAT : GL_CLAMP);
        
        // Done setting image parameters
        //glDisable(GL_TEXTURE_2D);
        
        // Release internal buffer
        stbi_image_free(DataBuffer);
        
        // Place in post-back as desired
        if(Width != NULL)
            *Width = Image.Width;
        if(Height != NULL)
            *Height = Image.Height;
        if(Channels != NULL)
            *Channels = Image.Channels;
        
        // Save to dictionary
        __g2ImageList.insert(std::pair<std::string, __g2Image>(std::string(Image.FileName), Image));

        std::cout<<glGetError()<<std::endl;
        return Image.GlTextureID;
    }
    // Image around found, return that result
    else
    {
        // Post and return what was already known
        if(Width != NULL)
            *Width = Result->second.Width;
        if(Height != NULL)
            *Height = Result->second.Height;
        if(Channels != NULL)
            *Channels = Result->second.Channels;
        return Result->second.GlTextureID;
    }
}

void g2LoadImageBuffer(const char* ImagePath, unsigned char** OutBuffer, int* Width, int* Height, int* Channels)
{
    // Create temporary retainers
    int TempWidth, TempHeight, TempChannels;
    
    // Allocate image; fail out on error
    *OutBuffer = stbi_load(ImagePath, &TempWidth, &TempHeight, &TempChannels, 4);
    if(Width != NULL)
        *Width = TempWidth;
    if(Height != NULL)
        *Height = TempHeight;
    if(Channels != NULL)
        *Channels = TempChannels;
}

void g2UnloadImageBuffer(unsigned char* OutBuffer)
{
    stbi_image_free(OutBuffer);
}
