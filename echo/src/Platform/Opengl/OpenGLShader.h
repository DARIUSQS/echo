#include "Shader.h"
#include "ecpch.h"
#include <GL/gl.h>

namespace Echo
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader(const std::string& path);
            virtual ~OpenGLShader();

            virtual void Bind() const override;
            virtual void unBind() const override;
                
            void Compile(const std::unordered_map<unsigned int, std::string>& shaders);
            std::string ReadFile(const std::string& path);
            std::unordered_map<unsigned int, std::string> PreProcessShaders(const std::string& string);
            unsigned int CreateShaders(GLenum shaderType, const std::string& shaderSrc);

            void UploadUniformMat4(const glm::mat4& matrix, const std::string& name);
            void UploadUniformVec4(const glm::vec4& vec4, const std::string& name);
            void UploadUniformVec3(const glm::vec3& vec4, const std::string& name);
            void UploadUniformInt(int value, const std::string& name);
            void UploadUniformFloat(float value, const std::string& name);
        private:
            u_int32_t m_RendererID;
    };
}
