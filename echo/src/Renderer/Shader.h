#pragma once
#include <glm/glm.hpp>

namespace Echo
{
    class Shader
    {
    public:
        virtual ~Shader() = default;  

        virtual inline std::pair<std::string, std::string> GetShaders() const = 0;

        virtual inline void Bind() const = 0;
        virtual inline void unBind() const = 0;

        static Shader* Create(const std::string& shaderSourcePath);
    };
}
