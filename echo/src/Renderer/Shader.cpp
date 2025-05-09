#include "Shader.h"
#include <glad.h>
#include <sstream>
#include <fstream>

namespace Echo 
{
    Shader::Shader(const std::string& shaderSourcePath)
    {
        std::stringstream shaders[2]; // vertex  fragment
        std::string line;
        std::ifstream fin(shaderSourcePath);
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
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    unsigned int Shader::Create(unsigned int shaderType, const std::string& shaderSrc)
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
    
    void Shader::Compile()
    {
        unsigned int vertex = Create(GL_VERTEX_SHADER, m_VertexShader);    
        unsigned int fragment = Create(GL_FRAGMENT_SHADER, m_FragmentShader);    

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

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::unBind() const
    {
        glUseProgram(0);
    }
}
