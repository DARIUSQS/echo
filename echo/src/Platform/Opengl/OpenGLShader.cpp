#include <glad.h>
#include "Platform/Opengl/OpenGLShader.h"
#include "ecpch.h"
#include <glm/gtc/type_ptr.hpp>

namespace Echo 
{
    static GLenum ParseShaderTypeFromString(const std::string& type)
    {
        if(type == "vertex") return GL_VERTEX_SHADER;
        else if(type == "fragment") return GL_FRAGMENT_SHADER; 
        
        EC_WARN("Shader type: " + type);
        EC_ASSERT(false, "Shader type not supported");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& shaderSourcePath)
    {
        std::string shadersSource = ReadFile(shaderSourcePath);
        auto shaders = PreProcessShaders(shadersSource);
        Compile(shaders);
    }
    
    std::string OpenGLShader::ReadFile(const std::string& path)
    {
        std::string result;
        std::ifstream fin(path, std::ios::binary);
        if(fin)
        {
            fin.seekg(0, std::ios::end);
            result.resize(fin.tellg());
            fin.seekg(0, std::ios::beg);
            fin.read(&result[0], result.size());
            fin.close();
        }
        else 
        {
            EC_ASSERT(0, "Shader file couldn't be read");
        }
        return result;
    }
    
    std::unordered_map<unsigned int, std::string> OpenGLShader::PreProcessShaders(const std::string& string)
    {
        std::unordered_map<GLenum, std::string> Shaders;
        const char* token = "#shader";
        size_t tokenSize = strlen(token);
        size_t pos = string.find(token, 0);
        while(pos != std::string::npos)
        {
            size_t end = string.find_first_of("\r\n", pos);
            EC_ASSERT(end != std::string::npos, "Shader File Syntax Error");
            size_t startType = pos + tokenSize + 1;
            std::string type = string.substr(startType, end - startType);
            EC_ASSERT(type == "fragment" || type == "vertex", "Shader Type not supported");
            
            size_t startPos = string.find_first_not_of("\r\n", end);
            pos = string.find(token, startPos);
            Shaders[ParseShaderTypeFromString(type)] = string.substr(startPos,
                    (pos == std::string::npos ? string.size() - 1 : pos - 1) - startPos);
        }
        return Shaders;
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    unsigned int OpenGLShader::CreateShaders(GLenum shaderType, const std::string& shaderSrc)
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
    
    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaders)
    {
        m_RendererID = glCreateProgram();
        std::vector<unsigned int> shadersID;
        shadersID.reserve(shaders.size());

        for(auto sh : shaders)
        {
            EC_WARN(sh.second);
            unsigned int shaderID = CreateShaders(sh.first, sh.second);    
            glAttachShader(m_RendererID, shaderID);
            shadersID.push_back(shaderID);
        }
        glLinkProgram(m_RendererID);
 
        int success;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
            EC_ERROR("SHADER::PROGRAM::LINKING_FAILED {0}", infoLog);
        }
            
        for(unsigned int ID : shadersID)
        {
            glDeleteShader(ID);
        }
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
