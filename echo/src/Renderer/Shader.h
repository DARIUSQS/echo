#pragma once
#include <glm/glm.hpp>

namespace Echo
{
    class Shader
    {
    public:
        virtual ~Shader() = default;  

        virtual void Bind() const = 0;
        virtual void unBind() const = 0;

        static Shader* Create(const std::string& shaderSourcePath);
    };
}
