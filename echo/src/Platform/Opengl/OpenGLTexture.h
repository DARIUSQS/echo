#include "Texture.h"

namespace Echo
{
    class OpenGLTexture2D : public Texture2D 
    {
        public: 
            OpenGLTexture2D(const std::string& path);
            ~OpenGLTexture2D();

            virtual inline uint32_t GetWidth() const override {return m_Width;};
            virtual inline uint32_t GetHeight() const override {return m_Height;};

            virtual void Bind(uint32_t slot) const override;
        private:
            std::string m_Path;
            uint32_t m_RendererID;
            uint32_t m_Width, m_Height;
    };
}
