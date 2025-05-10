#pragma once 
#include "ecpch.h"

namespace Echo 
{
    enum class ShaderDataType
    {
        None, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeTotalSize(ShaderDataType type)
    {
        switch (type) 
        {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3: return 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
        }
        EC_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type) 
        {
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3: return 9;
            case ShaderDataType::Mat4: return 16;
            case ShaderDataType::Int: return 1;
            case ShaderDataType::Int2: return 2;
            case ShaderDataType::Int3: return 3;
            case ShaderDataType::Int4: return 4;
            case ShaderDataType::Bool: return 1;
        }
        EC_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

    struct BufferLayoutData 
    {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        public:
        BufferLayoutData(ShaderDataType type, const std::string& name)
            : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0)
        {
        }
    };

    class BufferLayout 
    {
        public:
            BufferLayout(const std::initializer_list<BufferLayoutData>& elements)
                :m_Elements(elements) 
            {
                CalculateOffsetsAndStride();
            }

            BufferLayout() {}
            
            uint32_t inline GetStride() const {return m_Stride;}
            std::vector<BufferLayoutData>::iterator begin() {return m_Elements.begin();}
            std::vector<BufferLayoutData>::iterator end() {return m_Elements.end();}    
            
        private:
            void CalculateOffsetsAndStride()
            {
                m_Stride = 0;
                for(auto& element : m_Elements)
                {
                    element.offset = m_Stride;
                    m_Stride += ShaderDataTypeTotalSize(element.type);
                }
            }
            std::vector<BufferLayoutData> m_Elements;
            uint32_t m_Stride = 0;
    };

    class VertexBuffer 
    {
        public:
            virtual ~VertexBuffer() {};

            virtual void Bind() const = 0;
            virtual void unBind() const = 0;
            
            static VertexBuffer* Create(float* vertices, uint32_t size);
            virtual const BufferLayout& GetLayout() const = 0;
            virtual void SetLayout(const BufferLayout& layout) = 0;
    };

    class IndexBuffer
    {
        public:
            virtual ~IndexBuffer() {};

            virtual void Bind() const = 0;
            virtual void unBind() const = 0;
            
            static IndexBuffer* Create(unsigned int* indices, uint32_t size);
    }; 
}
