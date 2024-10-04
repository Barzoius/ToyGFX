#pragma once

#include "IndexedTrigList.h"

class Cube
{
public:
    template<typename VERTEX>
    static IndexedTrigList<VERTEX> Make()
    {
        constexpr float side = 1.0f / 2.0f;
        //glm::vec3
        std::vector<glm::vec3> vertices;

        vertices.emplace_back(-side, -side, -side);
        vertices.emplace_back(side, -side, -side);
        vertices.emplace_back(-side, side, -side);
        vertices.emplace_back(side, side, -side);
        vertices.emplace_back(-side, -side, side);
        vertices.emplace_back(side, -side, side);
        vertices.emplace_back(-side, side, side);
        vertices.emplace_back(side, side, side);

        std::vector<glm::vec3> adjustedVertices;
        adjustedVertices.emplace_back(-side, -side, -side);        // Vertex 0 (unchanged)
        adjustedVertices.emplace_back(side, -side, -side);         // Vertex 1 (unchanged)
        adjustedVertices.emplace_back(-side, side, -side);         // Vertex 2 (unchanged)
        adjustedVertices.emplace_back(side, side, -side);          // Vertex 3 (unchanged)
        adjustedVertices.emplace_back(-side, -side, side * 0.5f); // Vertex 4 (raise top side)
        adjustedVertices.emplace_back(side, -side, side * 0.5f);   // Vertex 5 (raise top side)
        adjustedVertices.emplace_back(-side, side, side * 0.5f);   // Vertex 6 (raise top side)
        adjustedVertices.emplace_back(side, side, side * 0.5f);    // Vertex 7 (raise top side)

        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = adjustedVertices[i];
        }

        return{
            std::move(verts),{
                0,2,1, 2,3,1,
                1,3,5, 3,7,5,
                2,6,3, 3,6,7,
                4,5,7, 4,7,6,
                0,4,2, 2,4,6,
                0,1,4, 1,5,4
            }
        };
    }
};