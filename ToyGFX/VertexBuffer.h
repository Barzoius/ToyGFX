#pragma once

#include "Bindable.h"

#include <vector>

#include "glm\common.hpp"
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class VertexBuffer : public Bindable
{
public:
    template <typename VERTEX>
    VertexBuffer(std::vector<VERTEX>& vertices)
        //:
        //mVertices(vertices)
    {
        mVertices.reserve(vertices.size());
        for (const auto& vertex : vertices)
        {
            mVertices.push_back(vertex.pos);  // Assuming VERTEX has a glm::vec3 'pos' field
        }
        glGenBuffers(1, &ID);
    }
    ~VertexBuffer();

    void Bind() override;


private:
    GLuint ID;
    std::vector<glm::vec3> mVertices;
};