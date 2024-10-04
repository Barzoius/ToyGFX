#pragma once

#include "Bindable.h"

#include <vector>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>


template<typename VERTEX>
class VertexBuffer : public Bindable
{
public:
    VertexBuffer(const std::vector<VERTEX>& vertices)
        : sizeVERTEX(sizeof(VERTEX))
    {
        mVertices.reserve(vertices.size());

        for (const auto& vertex : vertices)
        {
            mVertices.push_back(vertex);  
        }

        glGenBuffers(1, &ID);
    }

    ~VertexBuffer() = default;

   // void Bind() override;

    void Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeVERTEX, mVertices.data(), GL_STATIC_DRAW);
    }

    //size_t GetVertexSize() const;


    size_t GetVertexSize() const
    {
        return sizeVERTEX;
    }

private:
    GLuint ID;
    size_t sizeVERTEX;
    std::vector<VERTEX> mVertices; 
};
