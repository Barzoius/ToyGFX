#pragma once

#include "IndexedTrigList.h"

class Square
{
public:
    template<typename VERTEX>
    static IndexedTrigList<VERTEX> Make()
    {
        constexpr float side = 1.0f / 2.0f;

        std::vector<glm::vec3> vertices = {
            { 0.5f,  0.5f, 0.0f },  // Top right
            { 0.5f, -0.5f, 0.0f },  // Bottom right
            {-0.5f, -0.5f, 0.0f },  // Bottom left
            {-0.5f,  0.5f, 0.0f }   // Top left
        };

        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = vertices[i];
        }
   

        return{
            std::move(verts),{
            0, 1, 3,
            1, 2, 3
            }
        };
    }
};