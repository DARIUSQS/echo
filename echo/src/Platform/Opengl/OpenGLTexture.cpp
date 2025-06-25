#include "OpenGLTexture.h"
#include <glad.h>
#include "stb_image.h"

namespace Echo 
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        :m_Path(path)
    {
        int width, height, channels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        EC_ASSERT(data, "Failed to load texture!");
        m_Width = width;
        m_Height = height;

        GLenum internalformat, format;

        if(channels == 3)
        {
            internalformat = GL_RGB8;
            format = GL_RGB;
        }
        else if(channels == 4)
        {
            internalformat = GL_RGBA8;
            format = GL_RGBA;
        }
        EC_ASSERT(internalformat & format, "Texture Channel number isn't supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalformat, m_Width, m_Height);
        
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }
}

