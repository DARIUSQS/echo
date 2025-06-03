#pragma once
#include <glm/glm.hpp>

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

        void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);

        void Bind() const;
        void unBind() const;
    private:
        std::string m_VertexShader, m_FragmentShader;
        unsigned int m_RendererID;
    };
}
