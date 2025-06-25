#include "Platform/Opengl/OpenGLShader.h"
#include "glad.h"
#include "ecpch.h"
#include <glm/gtc/type_ptr.hpp>

namespace Echo 
{
    OpenGLShader::OpenGLShader(const std::string& shaderSourcePath)
    {
        std::stringstream shaders[2]; // vertex  fragment
        std::string line;
        std::ifstream fin(shaderSourcePath, std::ios::binary);
        bool shaderindex = 0;
        while(std::getline(fin, line))
        {
            if(line.find("#shader") != std::string::npos)
            {
                if(line.find("vertex") != std::string::npos) shaderindex = 0;
                else if(line.find("fragment") != std::string::npos) shaderindex = 1;
            }
            else 
            {
                shaders[shaderindex] << line << '\n';
            }
        }
        m_VertexShader = shaders[0].str();
        m_FragmentShader = shaders[1].str();
        fin.close();

        Compile();
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    unsigned int OpenGLShader::CreateShaders(unsigned int shaderType, const std::string& shaderSrc)
    {
        unsigned int shader;

        shader = glCreateShader(shaderType);
        const GLchar* shaderSource = shaderSrc.c_str();
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            EC_ERROR("SHADER::VERTEX::COMPILATION_FAILED {0}", infoLog);
        };
        return shader;
    }
    
    void OpenGLShader::Compile()
    {
        unsigned int vertex = CreateShaders(GL_VERTEX_SHADER, m_VertexShader);    
        unsigned int fragment = CreateShaders(GL_FRAGMENT_SHADER, m_FragmentShader);    

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertex);
        glAttachShader(m_RendererID, fragment);
        glLinkProgram(m_RendererID);
 
        int success;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
            EC_ERROR("SHADER::PROGRAM::LINKING_FAILED {0}", infoLog);
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void OpenGLShader::UploadUniformMat4(const glm::mat4& matrix, const std::string& name)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, 0, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformVec4(const glm::vec4& vec4, const std::string& name)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
    }
    
    void OpenGLShader::UploadUniformInt(int value, const std::string& name)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::unBind() const
    {
        glUseProgram(0);
    }
}
