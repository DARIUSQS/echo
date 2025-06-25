#include "Shader.h"

namespace Echo
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader(const std::string& path);
            virtual ~OpenGLShader();

            virtual inline std::pair<std::string, std::string> GetShaders() const override {return {m_VertexShader, m_FragmentShader};}

            virtual void Bind() const override;
            virtual void unBind() const override;
                
            void Compile();
            unsigned int CreateShaders(unsigned int shaderType, const std::string& shaderSrc);


            void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);
            void UploadUniformVec4(const glm::vec4& vec4, const std::string& name);
            void UploadUniformInt(int value, const std::string& name);

        private:
            u_int32_t m_RendererID;
            std::string m_VertexShader, m_FragmentShader;
    };
}
