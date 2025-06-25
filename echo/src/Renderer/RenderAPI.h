#pragma once
#include <glm/glm.hpp>
#include <VertexArray.h>
namespace Echo
{
    
    class RendererAPI
    {
        public:
            enum class API 
            {
                None, OpenGL
            };
            virtual void Init() = 0;

            virtual void SetClearColor(const glm::vec4& color) = 0;
            virtual void Clear() = 0;

            virtual void DrawIndex(const Ref<VertexArray>& vao) = 0;

            static inline API GetAPI() { return s_API;}
        private:
            static API s_API;
    };

};
