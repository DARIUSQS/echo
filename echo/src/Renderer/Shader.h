#pragma once

namespace Echo
{
    class Shader
    {
    public:
        Shader(const std::string& shaderSourcePath);
        ~Shader(); 
        void Compile();
        unsigned int Create(unsigned int shaderType, const std::string& shaderSrc);
        inline std::pair<std::string, std::string> GetShaders() const {return {m_VertexShader, m_FragmentShader};}
        void Bind() const;
        void unBind() const;
    private:
        std::string m_VertexShader, m_FragmentShader;
        unsigned int m_RendererID;
    };
}
