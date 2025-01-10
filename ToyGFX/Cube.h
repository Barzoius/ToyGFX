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
        std::vector<glm::vec3> normals;

        vertices.emplace_back(-side, -side, -side);
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(side, -side, -side); 
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(-side, side, -side);
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(side, side, -side);
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(-side, -side, side); 
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(side, -side, side); 
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(-side, side, side); 
        normals.emplace_back(0.0f, 0.0f, -1.0f);

        vertices.emplace_back(side, side, side); 
        normals.emplace_back(0.0f, 0.0f, -1.0f);


        //std::vector<glm::vec3> colors =
        //{
        //    {0.0f, 1.0f, 0.0f},
        //    {0.0f, 0.0f, 1.0f},
        //    {1.0f, 0.0f, .0f},
        //    {0.0f, 0.0f, 0.0f},

        //    {0.0f, 1.0f, 0.0f},
        //    {0.0f, 0.0f, 1.0f},
        //    {1.0f, 0.0f, .0f},
        //    {0.0f, 0.0f, 0.0f}
        //}


        std::vector<VERTEX> verts(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts[i].pos = vertices[i];
            verts[i].n = normals[i];
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