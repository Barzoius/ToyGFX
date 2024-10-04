#pragma once

#include "IndexedTrigList.h"

class Square
{
public:
    template<typename VERTEX>
    static IndexedTrigList<VERTEX> Make()
    {

        std::vector<glm::vec3> vertices = {
            { 0.5f,  0.5f, 0.0f },  // Top right
            { 0.5f, -0.5f, 0.0f },  // Bottom right
            {-0.5f, -0.5f, 0.0f },  // Bottom left
            {-0.5f,  0.5f, 0.0f }   // Top left
        };

        std::vector<glm::vec3> colors = {
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, .0f},
            {0.0f, 0.0f, 0.0f}
        };

        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = vertices[i];
            verts[i].col = colors[i];
        }
   
        return{
            std::move(verts),{
            0, 1, 3,
            1, 2, 3
            }
        };
    }
};